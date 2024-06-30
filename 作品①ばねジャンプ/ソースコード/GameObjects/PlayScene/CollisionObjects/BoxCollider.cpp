//--------------------------------------------------------------------------------------
// File: BoxCollider.cpp
//
// 箱の当たり判定クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BoxCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転</param>
/// <param name="sca">拡大率</param>
BoxCollider::BoxCollider(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	CollisionObject(CollisionType::Box, pos, rot, sca)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	
	//	箱の作成
	m_geometricPrimitive = GeometricPrimitive::CreateBox(context, SimpleMath::Vector3::One);

	//	半径
	float r = (sca / 2.0f).Length();

	//	拡大率に応じた球の当たり判定の作成
	m_sphereCollider = std::make_unique<SphereCollider>(pos, r);
}

/// <summary>
/// デストラクタ
/// </summary>
BoxCollider::~BoxCollider()
{

}

/// <summary>
/// 当たり判定の更新
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rotate">回転</param>
/// <param name="sca">拡大率</param>
void BoxCollider::ColliderUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rotate,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	座標の更新
	SetPos(pos);
	//	回転の更新
	SetRotQua(rotate);
	//	拡大率の更新
	SetSca(sca);

	//	各軸の計算
 	SetForward(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -1.0f), rotate));
	SetHorizontal(SimpleMath::Vector3::Transform(SimpleMath::Vector3(1.0f, 0.0f, 0.0f), rotate));
	SetVertical(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 1.0f, 0.0f), rotate));

	//	各面の法線ベクトルの計算
	m_normal[0] = -GetForward();
	m_normal[1] = -GetHorizontal();
	m_normal[2] = GetVertical();
	m_normal[3] = -GetVertical();
	m_normal[4] = GetHorizontal();
	m_normal[5] = GetForward();

	//	球の当たり判定の更新
	m_sphereCollider->ColliderUpdate(pos, rotate, sca);
}

/// <summary>
/// 当たり判定の描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void BoxCollider::ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	//	ワールド行列の計算
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	拡大率
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	座標
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	world = sca * rot * trans;

	//	ジオメトリの描画
	m_geometricPrimitive->Draw(world, view, proj, Colors::White * 0.5f);

	//	球の描画
	m_sphereCollider->ColliderRender(view, proj);
}