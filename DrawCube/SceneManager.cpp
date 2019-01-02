//*****************************************************************************
// シーンマネージャクラス[SceneManager.cpp]
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "SceneManager.h"
#include "Renderer.h"
#include "Cube.h"
#include "Utility.h"

//=============================================================================
// コンストラクタ
//=============================================================================
SceneManager::SceneManager()
{
	_pRenderer = nullptr;
	_pCube = nullptr;
	_pCube2 = nullptr;

	_drawableObjects.reserve(2);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneManager::~SceneManager()
{
}

//=============================================================================
// インスタンス生成処理
// pRenderer : 描画に使用するレンダラー
//=============================================================================
SceneManager* SceneManager::CreateInstance(Renderer* pRenderer)
{
	SceneManager* pSceneManager = new SceneManager();
	pSceneManager->Init(pRenderer);

	return pSceneManager;
}

//=============================================================================
// 初期化処理
// pRenderer : 描画に使用するレンダラー
//=============================================================================
HRESULT SceneManager::Init(Renderer* pRenderer)
{
	_pRenderer = pRenderer;
	_pCube = Cube::CreateInstance(_pRenderer->GetDevice());
	_pCube->SetPosition(20.0f, 0.0f, 0.0f);
	_drawableObjects.push_back(_pCube);

	_pCube2 = Cube::CreateInstance(_pRenderer->GetDevice());
	_pCube2->SetPosition(-20.0f, 0.0f, 0.0f);
	_drawableObjects.push_back(_pCube2);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneManager::Uninit()
{
	SafeUninitAndDelete(_pCube);
	SafeUninitAndDelete(_pCube2);
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneManager::Update()
{
	_pCube->Update();
	_pCube2->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneManager::Draw()
{
	_pRenderer->Draw(_drawableObjects);
}