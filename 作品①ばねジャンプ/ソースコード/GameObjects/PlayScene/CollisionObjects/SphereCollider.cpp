//--------------------------------------------------------------------------------------
// File: SphereCollider.cpp
//
// 球の当たり判定クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SphereCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">当たり判定の座標</param>
/// <param name="radius">球の半径</param>
SphereCollider::SphereCollider(const DirectX::SimpleMath::Vector3& pos, const float& radius) :
	CollisionObject(CollisionType::Sphere, pos),
	m_radius(radius)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	
	//	球の作成(直径)
	m_geometricPrimitive = GeometricPrimitive::CreateSphere(context, m_radius * 2.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
SphereCollider::~SphereCollider()
{

}

/// <summary>
/// 当たり判定の更新
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rotate">回転</param>
/// <param name="sca">拡大率</param>
void SphereCollider::ColliderUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rotate,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	座標の更新
	SetPos(pos);
}

/// <summary>
/// 当たり判定の描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void SphereCollider::ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	//	ワールド行列の計算
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	座標
	world*= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	ジオメトリの描画
	m_geometricPrimitive->Draw(world, view, proj, Colors::White * 0.5f);
}