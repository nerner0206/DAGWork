//--------------------------------------------------------------------------------------
// File: DebugCamera.cpp
//
// デバッグカメラクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DebugCamera.h"

using namespace DirectX;

//	カメラの距離
const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// コンストラクタ
/// </summary>
DebugCamera::DebugCamera() :
	m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_sx(0.0f), m_sy(0.0f),
	m_scrollWheelValue(0.0f)
{
	// マウスのフォイール値をリセット
	Mouse::Get().ResetScrollWheelValue();

	//	ウィンドウサイズの設定
	SetWindowSize(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT);
}

/// <summary>
/// デストラクタ
/// </summary>
DebugCamera::~DebugCamera()
{

}

/// <summary>
/// 更新
/// </summary>
void DebugCamera::Update()
{
	auto state = Mouse::Get().GetState();

	// 相対モードなら何もしない
	if (state.positionMode == Mouse::MODE_RELATIVE) return;

	m_tracker.Update(state);

	// マウスの左ボタンが押された
	if (m_tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// マウスの座標を取得
		m_x = state.x;
		m_y = state.y;
	}
	else if (m_tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// 現在の回転を保存
		m_xAngle = m_xTmp;
		m_yAngle = m_yTmp;
	}
	// マウスのボタンが押されていたらカメラを移動させる
	if (state.rightButton)
	{
		Motion(state.x, state.y);
	}

	// マウスのフォイール値を取得
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		Mouse::Get().ResetScrollWheelValue();
	}

	// ビュー行列を算出する
	SimpleMath::Matrix rotY = SimpleMath::Matrix::CreateRotationY(m_yTmp);
	SimpleMath::Matrix rotX = SimpleMath::Matrix::CreateRotationX(m_xTmp);

	SimpleMath::Matrix rt = rotY * rotX;

	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 eye(0.0f, 3.0f, 3.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	eye = SimpleMath::Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = SimpleMath::Vector3::Transform(up, rt.Invert());

	SetPos(eye);
	SetTargetPosition(target);

	//	ビュー行列の計算
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(GetPos(), GetTargetPosition(), SimpleMath::Vector3::Up);
	//	ビュー行列の設定
	SetViewMatrix(view);
}

/// <summary>
/// カメラの移動
/// </summary>
/// <param name="x">マウスのX座標</param>
/// <param name="y">マウスのY座標</param>
void DebugCamera::Motion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}