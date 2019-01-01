﻿//*****************************************************************************
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

	_drawableObjects.reserve(1);
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

	_drawableObjects.push_back(_pCube);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneManager::Uninit()
{
	SafeUninitAndDelete(_pCube);
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneManager::Update()
{
	_pCube->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneManager::Draw()
{
	_pRenderer->Draw(_drawableObjects);
}