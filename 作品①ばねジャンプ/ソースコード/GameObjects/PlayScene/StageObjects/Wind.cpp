//--------------------------------------------------------------------------------------
// File: Wind.cpp
//
// 風クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Wind.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/Particle/WindParticle.h"

using namespace DirectX;

//	データアクセス用文字列
const std::string Wind::POWER_STR = "Power";

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <param name="power">風力</param>
Wind::Wind(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& power) :
	IStageObject(StageObjType::Wind, pos, rot, sca),
	m_power(power),
	m_isHit(false),
	m_player(nullptr)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Wind::~Wind()
{

}

/// <summary>
/// 初期化
/// </summary>
void Wind::Initialize()
{
	//	当たり判定の生成
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());
	//	当たり判定の情報を更新する
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の設定
	SetCollisionObject(std::move(boxCollider));

	//	風向き
	m_vector = SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, GetRotQua());

	//	パーティクルの生成
	m_windParticle = std::make_unique<WindParticle>(this);
	//	初期化
	m_windParticle->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void Wind::Update(const float& elapsedTime)
{
	//	当たり判定
	Collider collider;

	//	プレイヤーの当たり判定
	if (collider.BoxToBoxCheck(m_player->GetBoxCollider(), GetCollisionObject()))
	{
		//	衝突開始判定
		if (!m_isHit)
		{
			//	風音の再生
			GetAudioResources()->PlayWindSE();
			//	衝突済み
			m_isHit = true;
		}

		//	プレイヤーばねクラスへキャスト
		PlayerSpring* spring = dynamic_cast<PlayerSpring*>(m_player->GetPlayerSpring());

		//	速度の加算
		spring->AddVelocity(m_vector * m_power * elapsedTime);
	}
	else
	{
		//	衝突していない
		m_isHit = false;
	}

	//	パーティクルの更新
	m_windParticle->Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Wind::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	パーティクルの描画
	m_windParticle->Render(view, proj);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Wind::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{

}

/// <summary>
/// デバッグ描画
/// </summary>
void Wind::DebugRender()
{
	//	ステージオブジェクトの種類
	ImGui::Text("Wind");
	//	共通デバッグ描画
	CommonDebugRender();
	//	風力の変更
	ImGui::InputFloat(POWER_STR.c_str(), &m_power);
}

/// <summary>
/// 終了
/// </summary>
void Wind::Finalize()
{
	//	パーティクルの終了処理
	m_windParticle->Finalize();
}

/// <summary>
/// リセット
/// </summary>
void Wind::Reset()
{

}