//--------------------------------------------------------------------------------------
// File: BoxCollider.h
//
// 箱の当たり判定クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BOX_COLLIDER_DEFINED
#define BOX_COLLIDER_DEFINED

#include "SphereCollider.h"

/// <summary>
/// 箱の当たり判定クラス
/// </summary>
class BoxCollider : public CollisionObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="sca">拡大率</param>
	BoxCollider(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BoxCollider();
	
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
	/// 法線ベクトルの設定
	/// </summary>
	/// <param name="vel">法線ベクトル</param>
	/// <param name="num">面の番号</param>
	void SetNormal(const DirectX::SimpleMath::Vector3& vel, const int& num) { if (num >= 0 && num < 6) m_normal[num] = vel; }
	/// <summary>
	/// 法線ベクトルの取得
	/// </summary>
	/// <param name="num">面の番号</param>
	/// <returns>法線ベクトル</returns>
	DirectX::SimpleMath::Vector3 GetNormal(const int& num) const { 
		if (num >= 0 && num < 6) return m_normal[num]; 
		return DirectX::SimpleMath::Vector3::Zero; }

	/// <summary>
	/// 球の当たり判定の取得
	/// </summary>
	/// <returns>球の当たり判定クラスのポインタ</returns>
	SphereCollider* GetSphereCollider() { return m_sphereCollider.get(); }

private:
	//	ジオメトリクラスのユニークポインタ
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	//	面の法線ベクトル
	DirectX::SimpleMath::Vector3 m_normal[6];

	//	球の当たり判定クラスのユニークポインタ
	std::unique_ptr<SphereCollider> m_sphereCollider;
};
#endif // !BOX_COLLIDER_DEFINED