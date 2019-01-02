//*****************************************************************************
// キューブクラス[Cube.cpp]
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Cube.h"
#include "Utility.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Cube::Cube()
{
	_pVertexBuffer = nullptr;
	_pShaderResView = nullptr;
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
Cube::~Cube()
{
}

//=============================================================================
// インスタンス生成処理
// pDevice : デバイス
//=============================================================================
Cube * Cube::CreateInstance(ID3D11Device* pDevice)
{
	Cube* cube = new Cube();
	cube->Init(pDevice);

	return cube;
}

//=============================================================================
// 初期化処理
// pDevice : デバイス
//=============================================================================
void Cube::Init(ID3D11Device* pDevice)
{
	CreateVertexBuffer(pDevice);

	//// テクスチャ生成
	//D3DX11CreateShaderResourceViewFromFile(pDevice,
	//	"data/field004.jpg",
	//	NULL,
	//	NULL,
	//	&_pShaderResView,
	//	NULL);
}

//=============================================================================
// 頂点バッファ生成処理
// pDevice : デバイス
//=============================================================================
void Cube::CreateVertexBuffer(ID3D11Device* pDevice)
{
	// 頂点バッファ生成
	Vertex3D *pVertex = new Vertex3D[24];

	// 下
	pVertex[0].Position = XMFLOAT3(-10.0f, -10.0f, 10.0f);
	pVertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[0].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[0].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	pVertex[1].Position = XMFLOAT3(-10.0f, -10.0f, -10.0f);
	pVertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[1].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[1].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	pVertex[2].Position = XMFLOAT3(10.0f, -10.0f, 10.0f);
	pVertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[2].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[2].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	pVertex[3].Position = XMFLOAT3(10.0f, -10.0f, -10.0f);
	pVertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[3].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[3].Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	// 上
	pVertex[4].Position = XMFLOAT3(-10.0f, 10.0f, 10.0f);
	pVertex[4].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[4].Color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	pVertex[5].Position = XMFLOAT3(10.0f, 10.0f, 10.0f);
	pVertex[5].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[5].Color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[5].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	pVertex[6].Position = XMFLOAT3(-10.0f, 10.0f, -10.0f);
	pVertex[6].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[6].Color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[6].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	pVertex[7].Position = XMFLOAT3(10.0f, 10.0f, -10.0f);
	pVertex[7].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[7].Color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	pVertex[7].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// 手前
	pVertex[8].Position = XMFLOAT3(-10.0f, -10.0f, -10.0f);
	pVertex[8].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[8].Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[8].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	pVertex[9].Position = XMFLOAT3(-10.0f, 10.0f, -10.0f);
	pVertex[9].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[9].Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[9].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	pVertex[10].Position = XMFLOAT3(10.0f, -10.0f, -10.0f);
	pVertex[10].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[10].Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[10].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	pVertex[11].Position = XMFLOAT3(10.0f, 10.0f, -10.0f);
	pVertex[11].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[11].Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	pVertex[11].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// 奥
	pVertex[12].Position = XMFLOAT3(10.0f, -10.0f, 10.0f);
	pVertex[12].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[12].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	pVertex[12].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	pVertex[13].Position = XMFLOAT3(10.0f, 10.0f, 10.0f);
	pVertex[13].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[13].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	pVertex[13].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	pVertex[14].Position = XMFLOAT3(-10.0f, -10.0f, 10.0f);
	pVertex[14].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[14].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	pVertex[14].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	pVertex[15].Position = XMFLOAT3(-10.0f, 10.0f, 10.0f);
	pVertex[15].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[15].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	pVertex[15].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	// 右
	pVertex[16].Position = XMFLOAT3(10.0f, -10.0f, -10.0f);
	pVertex[16].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[16].Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[16].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	pVertex[17].Position = XMFLOAT3(10.0f, 10.0f, -10.0f);
	pVertex[17].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[17].Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[17].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	pVertex[18].Position = XMFLOAT3(10.0f, -10.0f, 10.0f);
	pVertex[18].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[18].Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[18].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	pVertex[19].Position = XMFLOAT3(10.0f, 10.0f, 10.0f);
	pVertex[19].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[19].Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	pVertex[19].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	// 左
	pVertex[20].Position = XMFLOAT3(-10.0f, -10.0f, 10.0f);
	pVertex[20].TexCoord = XMFLOAT2(0.0f, 1.0f);
	pVertex[20].Color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[20].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	pVertex[21].Position = XMFLOAT3(-10.0f, 10.0f, 10.0f);
	pVertex[21].TexCoord = XMFLOAT2(0.0f, 0.0f);
	pVertex[21].Color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[21].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	pVertex[22].Position = XMFLOAT3(-10.0f, -10.0f, -10.0f);
	pVertex[22].TexCoord = XMFLOAT2(1.0f, 1.0f);
	pVertex[22].Color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[22].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	pVertex[23].Position = XMFLOAT3(-10.0f, 10.0f, -10.0f);
	pVertex[23].TexCoord = XMFLOAT2(1.0f, 0.0f);
	pVertex[23].Color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	pVertex[23].Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex3D) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pVertex;

	pDevice->CreateBuffer(&bd, &sd, &_pVertexBuffer);

	SafeDelete(pVertex);
}

//=============================================================================
// 終了処理
//=============================================================================
void Cube::Uninit(void)
{
	SafeRelease(_pVertexBuffer);
	SafeRelease(_pShaderResView);
}

//=============================================================================
// 更新処理
//=============================================================================
void Cube::Update(void)
{
	_rotation.y += 0.0001f;
}

//=============================================================================
// 描画処理
// pContext : デバイスコンテキスト
// pVertexShader : 頂点シェーダー
// pPixelShader : ピクセルシェーダー
// pLayout : 頂点レイアウト
// pConstantBuffer : 定数バッファ
//=============================================================================
void Cube::Draw(ID3D11DeviceContext* pContext, ID3D11VertexShader* pVertexShader,
	ID3D11PixelShader* pPixelShader, ID3D11InputLayout* pLayout, ID3D11Buffer* pConstantBuffer)
{
	// 頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);

	// プリミティブタイプ設定
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 入力レイアウト設定
	pContext->IASetInputLayout(pLayout);

	// シェーダ設定
	pContext->VSSetShader(pVertexShader, nullptr, 0);
	pContext->PSSetShader(pPixelShader, nullptr, 0);

	// マトリクス設定
	XMMATRIX world, view, projection, worldViewProjection;

	world = XMMatrixIdentity();
	world = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	XMMATRIX invWorld;
	invWorld = XMMatrixIdentity();
	XMVECTOR tempVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	invWorld = XMMatrixInverse(&tempVec, world);

	world = world * XMMatrixTranslation(_position.x, _position.y, _position.z);

	view = XMMatrixLookAtLH(XMVectorSet(0.0f, 50.0f, -40.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	projection = XMMatrixPerspectiveFovLH(1.0f, (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
	worldViewProjection = world * view * projection;

	XMVECTOR light = XMVector3Normalize(XMVectorSet(0.0f, -1.0f, 1.0f, 0.0f));
	XMVECTOR localLight = XMVector3TransformCoord(light, invWorld);
	localLight = XMVector3Normalize(localLight);
	ConstantBuffer cb;
	XMStoreFloat4x4(&cb.World, XMMatrixTranspose(world));
	XMStoreFloat4x4(&cb.WorldViewProjection, XMMatrixTranspose(worldViewProjection));
	XMStoreFloat4(&cb.DirectionalLight, localLight);
	pContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb, 0, 0);
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

	// ポリゴン描画
	for (int nIndex = 0; nIndex < 6; ++nIndex)
	{
		pContext->Draw(4, nIndex * 4);
	}
}

void Cube::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}
