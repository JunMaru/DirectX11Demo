﻿//*****************************************************************************
// カメラクラス[Camera.cpp]
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Camera.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Camera::Camera()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
Camera::~Camera()
{
}

//=============================================================================
// インスタンス生成処理
// position : カメラ座標
// focusPoint : 注視点
//=============================================================================
Camera * Camera::CreateInstance(XMFLOAT3 position, XMFLOAT3 focusPoint)
{
	Camera* pCamera = new Camera();
	pCamera->Init(position, focusPoint);

	return pCamera;
}

//=============================================================================
// 初期化処理
// position : カメラ座標
// focusPoint : 注視点
//=============================================================================
void Camera::Init(XMFLOAT3 position, XMFLOAT3 focusPoint)
{
	_position = position;
	_focusPoint = focusPoint;
}

//=============================================================================
// 終了処理
//=============================================================================
void Camera::Uninit()
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Camera::Update()
{
}

//=============================================================================
// ビュープロジェクション行列の取得処理
// return : ビュープロジェクション行列
//=============================================================================
XMMATRIX Camera::GetViewProjectionMatrix()
{
	XMMATRIX view, projection;
	view = XMMatrixLookAtLH(
		XMVectorSet(_position.x, _position.y, _position.z, 1.0f),
		XMVectorSet(_focusPoint.x, _focusPoint.y, _focusPoint.z, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));

	projection = XMMatrixPerspectiveFovLH(1.0f, (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);

	return view * projection;
}