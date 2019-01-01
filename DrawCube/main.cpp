//*****************************************************************************
// メイン処理[main.cpp]
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Utility.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
constexpr auto WindowClassName = "AppClass";
constexpr auto WindowName = "DX11ポリゴン描画";

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
Renderer* g_pRenderer = nullptr;
SceneManager* g_pSceneManager = nullptr;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		WindowClassName,
		NULL
	};
	HWND hWnd;
	MSG msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		WindowClassName,
		WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(ScreenWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(ScreenHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			// 更新処理
			Update();

			// 描画処理
			Draw();
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(WindowClassName, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT result = S_OK;
	g_pRenderer = Renderer::CreateInstance(hInstance, hWnd, bWindow, &result);
	g_pSceneManager = SceneManager::CreateInstance(g_pRenderer);

	return result;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	SafeUninitAndDelete(g_pSceneManager);
	SafeUninitAndDelete(g_pRenderer);
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	g_pSceneManager->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	g_pSceneManager->Draw();
}