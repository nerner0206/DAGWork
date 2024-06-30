//--------------------------------------------------------------------------------------
// File: Collider.h
//
// 当たり判定クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#ifndef COLLIDER_DEFINED
#define COLLIDER_DEFINED

class CollisionObject;

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collider
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collider();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Collider();

	/// <summary>
	/// 球同士の当たり判定
	/// </summary>
	/// <param name="sph1">球の当たり判定クラスのポインタ1</param>
	/// <param name="sph2">球の当たり判定クラスのポインタ2</param>
	/// <returns>衝突判定</returns>
	bool SphereToSphereCheck(CollisionObject* sph1, CollisionObject* sph2);

	/// <summary>
	/// 球と箱の当たり判定
	/// </summary>
	/// <param name="sph">球の当たり判定クラスのポインタ</param>
	/// <param name="box">箱の当たり判定クラスのポインタ</param>
	/// <returns>衝突判定</returns>
	bool SphereToBoxCheck(CollisionObject* sph, CollisionObject* box);

	/// <summary>
	/// 箱同士の当たり判定
	/// </summary>
	/// <param name="box1">箱の当たり判定クラスのポインタ1</param>
	/// <param name="box2">箱の当たり判定クラスのポインタ2</param>
	/// <returns>衝突判定</returns>
	bool BoxToBoxCheck(CollisionObject* box1, CollisionObject* box2);

	/// <summary>
	/// 衝突面の算出①
	/// </summary>
	/// <param name="sph">球の当たり判定クラスのポインタ</param>
	/// <param name="box">箱の当たり判定クラスのポインタ</param>
	/// <returns>衝突面の番号</returns>
	int HitSurfaceNumber1(CollisionObject* sph, CollisionObject* box);
	/// <summary>
	/// 衝突面の算出②
	/// </summary>
	/// <param name="sph">球の当たり判定クラスのポインタ</param>
	/// <param name="box">箱の当たり判定クラスのポインタ</param>
	/// <returns>衝突面の番号</returns>
	int HitSurfaceNumber2(CollisionObject* sph, CollisionObject* box);

	/// <summary>
	/// めり込み量の取得
	/// </summary>
	/// <returns>めり込み量</returns>
	const float GetDistance() { return m_distance; }

private:
	//	めり込み量
	float m_distance;

	// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegOnSeparateAxis(
		const DirectX::SimpleMath::Vector3& sep,
		const DirectX::SimpleMath::Vector3& e1,
		const DirectX::SimpleMath::Vector3& e2,
		const DirectX::SimpleMath::Vector3& e3 = DirectX::SimpleMath::Vector3::Zero)
	{
		float r1 = fabsf(sep.Dot(e1));
		float r2 = fabsf(sep.Dot(e2));
		float r3 = 0.0f;
		if (e3 != DirectX::SimpleMath::Vector3::Zero) r3 = fabsf(sep.Dot(e3));

		return r1 + r2 + r3;
	}
};
#endif // !COLLIDER_DEFINED