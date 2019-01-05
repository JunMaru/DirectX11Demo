﻿//*****************************************************************************
// カメラクラス[Camera.h]
//*****************************************************************************
#pragma once

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Camera
{
public:
	//=============================================================================
	// デストラクタ
	//=============================================================================
	~Camera();

	//=============================================================================
	// インスタンス生成処理
	// position : カメラ座標
	// focusPoint : 注視点
	//=============================================================================
	static Camera* CreateInstance(XMFLOAT3 position, XMFLOAT3 focusPoint);

	//=============================================================================
	// 初期化処理
	// position : カメラ座標
	// focusPoint : 注視点
	//=============================================================================
	void Init(XMFLOAT3 position, XMFLOAT3 focusPoint);

	//=============================================================================
	// 終了処理
	//=============================================================================
	void Uninit();

	//=============================================================================
	// 更新処理
	//=============================================================================
	void Update();

	//=============================================================================
	// ビュープロジェクション行列の取得処理
	// return : ビュープロジェクション行列
	//=============================================================================
	XMMATRIX GetViewProjectionMatrix();

private:

	//=============================================================================
	// コンストラクタ
	//=============================================================================
	Camera();

	XMFLOAT3 _position;
	XMFLOAT3 _focusPoint;
};
