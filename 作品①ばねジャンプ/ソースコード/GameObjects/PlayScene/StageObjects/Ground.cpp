//--------------------------------------------------------------------------------------
// File: Ground.cpp
//
// 足場クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Ground.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
Ground::Ground(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	IStageObject(StageObjType::Cloud, pos, rot, sca),
	m_isShake(false),
	m_t(0.0f)
{
	//	揺れの拡大率
	m_defSca = sca;
	m_targetSca = sca;
	m_targetSca.x *= 1.05f;
	m_targetSca.z *= 1.05f;
}

/// <summary>
/// デストラクタ
/// </summary>
Ground::~Ground()
{

}

/// <summary>
/// 初期化
/// </summary>
void Ground::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_CLOUD_MODEL_PATH, *fx);
	//	モデルを設定する
	SetModel(std::move(model));

	//	当たり判定を生成
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の情報を更新する
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	球の当たり判定を設定する
	SetCollisionObject(std::move(boxCollider));
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void Ground::Update(const float& elapsedTime)
{
	//	雲の揺れ
	Shaking(elapsedTime);

	//	当たり判定の更新
	GetCollisionObject()->ColliderUpdate(GetPos(), GetRotQua(), GetSca());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Ground::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	モデルの描画
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, false);
		});
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Ground::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	拡大率
	SimpleMath::Matrix p_sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転
	SimpleMath::Matrix p_rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	移動
	SimpleMath::Matrix p_trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	ワールド行列の計算
	SimpleMath::Matrix world = p_sca * p_rot * p_trans;
	//	ワールド行列を設定する
	SetWorldMatrix(world);

	//	モデルの描画
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// デバッグ描画
/// </summary>
void Ground::DebugRender()
{
	//	ステージオブジェクトの種類
	ImGui::Text("Cloud");
	//	共通デバッグ描画
	CommonDebugRender();
}

/// <summary>
/// 終了
/// </summary>
void Ground::Finalize()
{

}

/// <summary>
/// リセット
/// </summary>
void Ground::Reset()
{
	SetIsHitActive(true);
}

/// <summary>
///	揺れる
/// </summary>
void Ground::Shaking(const float& elapsedTime)
{
	//	揺れない
	if (!m_isShake) return;

	//	補間率の増加
	m_t += elapsedTime;
	//	拡大率の設定
	SimpleMath::Vector3 sca = m_defSca;
	
	if (m_t > 0.5f)
	{
		//	3倍速
		m_t += elapsedTime * 2.0f;
		//	拡大率の変更
		sca = SimpleMath::Vector3::Lerp(m_targetSca, m_defSca, (m_t - 0.5f) * 2.0f);

		if (m_t > 1.0f)
		{
			m_t = 0.0f;
			m_isShake = false;
		}
	}
	else
	{
		//	拡大率の変更
		sca = SimpleMath::Vector3::Lerp(m_defSca, m_targetSca, m_t * 2.0f);
	}

	//	拡大率の設定
	SetSca(sca);
}