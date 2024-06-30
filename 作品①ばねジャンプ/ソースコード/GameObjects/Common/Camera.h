//--------------------------------------------------------------------------------------
// File: Camera.h
//
// カメラ基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef CAMERA_DEFINED
#define CAMERA_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// カメラ基底クラス
/// </summary>
class Camera : public Object
{
public:
	/// <summary>
	///	コンストラクタ
	/// </summary>
	Camera() :
		Object(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One),
		m_up(DirectX::SimpleMath::Vector3::Up) { }

	/// <summary>
	///	カメラの目標座標の取得
	/// </summary>
	/// <returns>目標座標</returns>
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	/// <summary>
	/// カメラの目標座標の設定
	/// </summary>
	/// <param name="target">目標座標</param>
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { m_target = target; }

	/// <summary>
	///	カメラの上方向の取得
	/// </summary>
	/// <returns>上方向</returns>
	const DirectX::SimpleMath::Vector3& GetUp() { return m_up; }
	/// <summary>
	/// カメラの上方向の設定
	/// </summary>
	/// <param name="up">上方向</param>
	void SetUp(const DirectX::SimpleMath::Vector3& up) { m_up = up; }

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	const DirectX::SimpleMath::Matrix GetViewMatrix() { return m_view; }
	/// <summary>
	/// ビュー行列の設定
	/// </summary>
	/// <param name="view">ビュー行列</param>
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }

public:
	/// <summary>
	///	仮想デストラクタ
	/// </summary>
	virtual ~Camera() = default;

private:
	//	カメラの目標座標
	DirectX::SimpleMath::Vector3 m_target;
	//	カメラの上方向
	DirectX::SimpleMath::Vector3 m_up;

	//	ビュー行列
	DirectX::SimpleMath::Matrix m_view;
};
#endif // !CAMERA_DEFINED
