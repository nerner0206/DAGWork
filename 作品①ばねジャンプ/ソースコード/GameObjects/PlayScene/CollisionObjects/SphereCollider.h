//--------------------------------------------------------------------------------------
// File: SphereCollider.h
//
// 球の当たり判定クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPHERE_COLLIDER_DEFINED
#define SPHERE_COLLIDER_DEFINED

#include "CollisionObject.h"

/// <summary>
/// 球の当たり判定クラス
/// </summary>
class SphereCollider : public CollisionObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">当たり判定の座標</param>
	/// <param name="radius">球の半径</param>
	SphereCollider(const DirectX::SimpleMath::Vector3& pos, const float& radius);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SphereCollider();

	/// <summary>
	/// 当たり判定の更新
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rotate">回転</param>
	/// <param name="sca">拡大率</param>
	void ColliderUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Vector3& sca) override;
	/// <summary>
	/// 当たり判定の描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 半径の設定
	/// </summary>
	/// <param name="r">球の半径</param>
	void SetRadius(const float& r) { m_radius = r; }
	/// <summary>
	/// 半径の取得
	/// </summary>
	/// <returns>球の半径</returns>
	float GetRadius() const { return m_radius; }

private:
	//	ジオメトリクラスのユニークポインタ
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	//	球の半径
	float m_radius;
};
#endif // !SPHERE_COLLIDER_DEFINED