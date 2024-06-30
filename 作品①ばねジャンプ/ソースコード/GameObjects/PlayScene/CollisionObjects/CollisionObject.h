//--------------------------------------------------------------------------------------
// File: CollisionObject.h
//
// 当たり判定基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef COLLISION_OBJECT_DEFINED
#define COLLISION_OBJECT_DEFINED

#include "GameObjects/Object.h"

#include <GeometricPrimitive.h>

//	当たり判定種類
enum class CollisionType
{
	Sphere = 0,
	Box,

	OverID
};

/// <summary>
/// 当たり判定基底クラス
/// </summary>
class CollisionObject : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">当たり判定の種類</param>
	/// <param name="pos">当たり判定の座標</param>
	/// <param name="rot">当たり判定の回転</param>
	/// <param name="sca">当たり判定の拡大率</param>
	CollisionObject(
		const CollisionType& type,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot = DirectX::SimpleMath::Quaternion::Identity,
		const DirectX::SimpleMath::Vector3& sca = DirectX::SimpleMath::Vector3::One) :
		Object(pos, rot, sca),
		m_type(type)
	{

	}

	//	種類の取得
	const CollisionType GetCollisionType() { return m_type; }
	//	種類の設定
	void SetCollisionType(const CollisionType& type) { m_type = type; }

	/// <summary>
	/// 正面方向の取得
	/// </summary>
	/// <returns>正面方向のベクトル</returns>
	const DirectX::SimpleMath::Vector3 GetForward() { return m_forward; }
	/// <summary>
	/// 正面方向の設定
	/// </summary>
	/// <param name="forward">正面方向のベクトル</param>
	void SetForward(const DirectX::SimpleMath::Vector3& forward) { m_forward = forward; }
	/// <summary>
	/// 水平方向の取得
	/// </summary>
	/// <returns>水平方向のベクトル</returns>
	const DirectX::SimpleMath::Vector3 GetHorizontal() { return m_horizontal; }
	/// <summary>
	/// 水平方向の設定
	/// </summary>
	/// <param name="horizontal">水平方向のベクトル</param>
	void SetHorizontal(const DirectX::SimpleMath::Vector3& horizontal) { m_horizontal = horizontal; }
	/// <summary>
	///	垂直方向の取得
	/// </summary>
	/// <returns>垂直方向のベクトル</returns>
	const DirectX::SimpleMath::Vector3 GetVertical() { return m_vertical; }
	/// <summary>
	/// 垂直方向の設定
	/// </summary>
	/// <param name="vertical">垂直方向のベクトル</param>
	void SetVertical(const DirectX::SimpleMath::Vector3& vertical) { m_vertical = vertical; }

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CollisionObject() = default;

	/// <summary>
	/// 当たり判定の更新
	/// </summary>
	/// <param name="pos">当たり判定の座標</param>
	/// <param name="rotate">当たり判定の回転</param>
	/// <param name="sca">当たり判定の拡大率</param>
	virtual void ColliderUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity,
		const DirectX::SimpleMath::Vector3& sca = DirectX::SimpleMath::Vector3::One) = 0;
	/// <summary>
	/// 当たり判定の描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void ColliderRender(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) = 0;

private:
	//	当たり判定種類
	CollisionType m_type;

	//	正面方向のベクトル
	DirectX::SimpleMath::Vector3 m_forward;
	//	水平方向
	DirectX::SimpleMath::Vector3 m_horizontal;
	//	垂直方向
	DirectX::SimpleMath::Vector3 m_vertical;
};
#endif // !COLLISION_OBJECT_DEFINED