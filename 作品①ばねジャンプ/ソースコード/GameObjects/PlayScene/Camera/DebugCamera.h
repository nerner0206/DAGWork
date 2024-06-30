//--------------------------------------------------------------------------------------
// File: DebugCamera.h
//
// デバッグカメラクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DEBUG_CAMERA_DEFINED
#define DEBUG_CAMERA_DEFINED

#include "GameObjects/Common/Camera.h"

/// <summary>
///	デバックカメラクラス
/// </summary>
class DebugCamera : public Camera
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugCamera();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DebugCamera();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:
	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

private:
	// 横回転
	float m_yAngle, m_yTmp;
	// 縦回転
	float m_xAngle, m_xTmp;

	// ドラッグされた座標
	int m_x, m_y;
	float m_sx, m_sy;

	// スクロールフォイール値
	int m_scrollWheelValue;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;

private:
	/// <summary>
	/// 画面サイズの設定
	/// </summary>
	/// <param name="windowWidth">ウインドウサイズ（幅）</param>
	/// <param name="windowHeight">ウインドウサイズ（高さ）</param>
	void SetWindowSize(const int& windowWidth, const int& windowHeight)
	{
		// 画面サイズに対する相対的なスケールに調整
		m_sx = 1.0f / float(windowWidth);
		m_sy = 1.0f / float(windowHeight);
	}

	/// <summary>
	/// カメラの移動
	/// </summary>
	/// <param name="x">マウスのX座標</param>
	/// <param name="y">マウスのY座標</param>
	void Motion(int x, int y);
};
#endif // !DEBUG_CAMERA_DEFINED

