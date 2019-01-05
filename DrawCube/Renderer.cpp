//*****************************************************************************
// レンダラークラス[Renderer.cpp]
// 現状はDirectX11のレンダラーとしての振る舞いをする
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Renderer.h"
#include "Utility.h"
#include "Interface/IDrawable.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Renderer::Renderer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
Renderer::~Renderer()
{
}

//=============================================================================
// インスタンス生成処理
// hInstance : インスタンスのハンドル
// hWnd : ウインドウのハンドル
// isWindow : ウインドウモードにするかどうか
// pResult : 結果格納先ポインタ
//=============================================================================
Renderer* Renderer::CreateInstance(HINSTANCE instance, HWND hWnd, bool isWindow, HRESULT* pResult)
{
	Renderer* pRenderer = new Renderer();
	*pResult = pRenderer->Init(instance, hWnd, isWindow);

	return pRenderer;
}

//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd : ウインドウのハンドル
// isWindow : ウインドウモードにするかどうか
//=============================================================================
HRESULT Renderer::Init(HINSTANCE instance, HWND hWnd, bool isWindow)
{
	HRESULT result = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = ScreenWidth;
	sd.BufferDesc.Height = ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;			// リフレッシュレート 1/60
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファ
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	result = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&_pSwapChain,
		&_pD3DDevice,
		&_featureLevel,
		&_pImmediateContext);

	if (FAILED(result))
	{
		return result;
	}

	D3D11_TEXTURE2D_DESC tex2DDesc;
	tex2DDesc.Width = sd.BufferDesc.Width;
	tex2DDesc.Height = sd.BufferDesc.Height;
	tex2DDesc.MipLevels = 1;
	tex2DDesc.ArraySize = 1;
	tex2DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2DDesc.SampleDesc = sd.SampleDesc;
	tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	tex2DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2DDesc.CPUAccessFlags = 0;
	tex2DDesc.MiscFlags = 0;

	_pD3DDevice->CreateTexture2D(&tex2DDesc, nullptr, &_pDepthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	depthStencilViewDesc.Format = tex2DDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Flags = 0;

	_pD3DDevice->CreateDepthStencilView(_pDepthTexture, &depthStencilViewDesc, &_pDepthStencilView);

	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = nullptr;
	_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	_pD3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
	pBackBuffer->Release();
	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, nullptr);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)ScreenWidth;
	vp.Height = (FLOAT)ScreenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_pImmediateContext->RSSetViewports(1, &vp);

	// 頂点シェーダコンパイル・生成
	ID3DBlob* pErrorBlob = nullptr;
	ID3DBlob* pVSBlob = nullptr;
	result = D3DX11CompileFromFile("Shader/HalfLambert.hlsl", nullptr, nullptr, "VertexShaderPolygon",
		"vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &pVSBlob, &pErrorBlob, nullptr);
	if (FAILED(result))
	{
		MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR);
	}

	_pD3DDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT numElements = ARRAYSIZE(layout);

	_pD3DDevice->CreateInputLayout(layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&_pVertexLayout);

	pVSBlob->Release();

	// ピクセルシェーダコンパイル・生成
	ID3DBlob* pPSBlob = nullptr;
	result = D3DX11CompileFromFile("Shader/HalfLambert.hlsl", nullptr, nullptr, "PixelShaderPolygon",
		"ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, nullptr, &pPSBlob, &pErrorBlob, nullptr);
	if (FAILED(result))
	{
		MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR);
	}

	_pD3DDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);

	pPSBlob->Release();

	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);
	result = _pD3DDevice->CreateBuffer(&hBufferDesc, nullptr, &_pConstantBuffer);
	if (FAILED(result))
	{
		MessageBox(hWnd, "Create ConstantBuffer", "Err", MB_ICONSTOP);
	}

	D3D11_RASTERIZER_DESC rasteriserDesc;
	rasteriserDesc.FillMode = D3D11_FILL_SOLID;
	rasteriserDesc.CullMode = D3D11_CULL_BACK;
	rasteriserDesc.FrontCounterClockwise = FALSE;
	rasteriserDesc.DepthClipEnable = TRUE;
	rasteriserDesc.MultisampleEnable = FALSE;
	rasteriserDesc.DepthBias = 0;
	rasteriserDesc.DepthBiasClamp = 0;
	rasteriserDesc.SlopeScaledDepthBias = 0;
	rasteriserDesc.AntialiasedLineEnable = FALSE;
	rasteriserDesc.ScissorEnable = FALSE;
	result = _pD3DDevice->CreateRasterizerState(&rasteriserDesc, &_pRasteriserState);

	if (FAILED(result))
	{
		MessageBox(hWnd, "Create RasterizerState", "Err", MB_ICONSTOP);
	}

	_pImmediateContext->RSSetState(_pRasteriserState);

	return result;
}

//=============================================================================
// 終了処理
//=============================================================================
void Renderer::Uninit()
{
	if (_pImmediateContext)
	{
		_pImmediateContext->ClearState();
		_pImmediateContext->Release();
		_pImmediateContext = nullptr;
	}

	SafeRelease(_pRasteriserState);
	SafeRelease(_pDepthStencilView);
	SafeRelease(_pDepthTexture);
	SafeRelease(_pVertexLayout);
	SafeRelease(_pVertexShader);
	SafeRelease(_pPixelShader);
	SafeRelease(_pRenderTargetView);
	SafeRelease(_pSwapChain);
	SafeRelease(_pConstantBuffer);
	SafeRelease(_pD3DDevice);
}

//=============================================================================
// 描画処理
// drawableObjects : 描画可能オブジェクト配列
// viewProjection : ビュープロジェクション行列
//=============================================================================
void Renderer::Draw(const std::vector<IDrawable*>& drawableObjects, const XMMATRIX& viewProjection)
{
	// バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	for (IDrawable* pDrawableObject : drawableObjects)
	{
		pDrawableObject->Draw(_pImmediateContext, _pVertexShader, _pPixelShader, _pVertexLayout, _pConstantBuffer, viewProjection);
	}

	_pSwapChain->Present(0, 0);
}

//=============================================================================
// デバイス取得処理
// return : デバイス
//=============================================================================
ID3D11Device* Renderer::GetDevice() const
{
	return _pD3DDevice;
}
