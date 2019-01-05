﻿//*****************************************************************************
// シーンマネージャクラス[SceneManager.h]
//*****************************************************************************
#pragma once

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class Cube;
class Renderer;
class Camera;
class IDrawable;

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class SceneManager
{
public:
	//=============================================================================
	// デストラクタ
	//=============================================================================
	~SceneManager();

	//=============================================================================
	// インスタンス生成処理
	// pRenderer : 描画に使用するレンダラー
	//=============================================================================
	static SceneManager* CreateInstance(Renderer* pRenderer);

	//=============================================================================
	// 終了処理
	//=============================================================================
	void Uninit(void);

	//=============================================================================
	// 更新処理
	//=============================================================================
	void Update(void);

	//=============================================================================
	// 描画処理
	//=============================================================================
	void Draw(void);

private:
	//=============================================================================
	// コンストラクタ
	//=============================================================================
	SceneManager();

	//=============================================================================
	// 初期化処理
	// pRenderer : 描画に使用するレンダラー
	//=============================================================================
	HRESULT Init(Renderer* pRenderer);

	std::vector<IDrawable*> _drawableObjects;
	Cube* _pCube;
	Cube* _pCube2;
	Renderer* _pRenderer;
	Camera* _pCamera;
};