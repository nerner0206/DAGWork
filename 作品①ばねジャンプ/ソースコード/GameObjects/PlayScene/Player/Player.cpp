//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// プレイヤークラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Player.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/Player/PlayerHead.h"

#include "GameObjects/PlayScene/Particle/JumpParticle.h"
#include "GameObjects/PlayScene/Particle/ExplosionParticle.h"

using namespace DirectX;

//	当たり判定のオフセット
const SimpleMath::Vector3 Player::COLLISION_POSITION_OFFSET = SimpleMath::Vector3(0.0f, 0.25f, 0.0f);
//	当たり判定の拡大率
const SimpleMath::Vector3 Player::COLLISION_SCALE = SimpleMath::Vector3(1.0f, 2.0f, 1.0f);

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() :
	m_playerSpring(nullptr),
	m_mouseSensitivity(1.0f),
	m_isGoal(false),
	m_isDead(false)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="startPos">初期座標</param>
void Player::Initialize(const DirectX::SimpleMath::Vector3& startPos)
{
	//	初期座標の初期化
	m_startPos = startPos;

	//	ばねの生成
	m_playerSpring = std::make_unique<PlayerSpring>(this);
	//	ばねの初期化
	m_playerSpring->Initialize(
		m_startPos,
		SimpleMath::Quaternion::Identity);

	//	当たり判定の生成
	m_boxCollider = std::make_unique<BoxCollider>(
		m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
		m_playerSpring->GetRotQua(),
		COLLISION_SCALE);

	//	フラグの初期化
	m_isGoal = false;
	m_isDead = false;

	//	ジャンプパーティクルの生成
	m_jumpParticle = std::make_unique<JumpParticle>();
	m_jumpParticle->Initialize();
	//	爆発パーティクルの生成
	m_explosionParticle = std::make_unique<ExplosionParticle>();
	m_explosionParticle->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="stageObjs">ステージ管理クラスのポインタ</param>
void Player::Update(const float& elapsedTime, StageManager* stageManager)
{
	//	頭のポインタにキャスト
	PlayerHead* head = dynamic_cast<PlayerHead*>(m_playerSpring->GetChild());

	if (!head->GetHit())
	{
		//	ばねの更新
		m_playerSpring->Update(
			elapsedTime,
			SimpleMath::Vector3::Zero,
			SimpleMath::Quaternion::Identity,
			stageManager);

		//	当たり判定の更新
		m_boxCollider->ColliderUpdate(
			m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
			m_playerSpring->GetRotQua(),
			COLLISION_SCALE);
	}

	//	ばねのポインタにキャスト
	PlayerSpring* spring = dynamic_cast<PlayerSpring*>(m_playerSpring.get());

	//	プレイヤーの死亡判定
	if ((head->GetHit() && !m_explosionParticle->GetActive()) ||
		m_playerSpring->GetPos().y < -10.0f)
	{
		//	死亡状態にする
		m_isDead = true;

		//	終了
		return;
	}

	//	ゴール判定（ばね部分のみ）
	m_isGoal = spring->GetIsGoal();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//	ばねの描画
	m_playerSpring->Render(view, proj);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Player::ShadowRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//	影描画
	m_playerSpring->ShadowRender(view, proj);
}

/// <summary>
/// デバッグ描画
/// </summary>
void Player::DebugRender()
{
	//	ウィンドウ色の設定
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_::ImGuiCond_Always);

	//	ウィンドウの設定
	ImGui::Begin("Player");

	//	ばねのデバッグ描画
	m_playerSpring->DebugRender();

	//	ウィンドウの終了
	ImGui::End();

	//	色の初期化
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

/// <summary>
/// 終了
/// </summary>
void Player::Finalize()
{
	//	ばねの終了処理
	m_playerSpring->Finalize();
}

/// <summary>
/// リセットする
/// </summary>
void Player::Reset()
{
	//	ばねをリセット
	m_playerSpring->Reset(
		m_startPos,
		SimpleMath::Quaternion::Identity);

	//	当たり判定の更新
	m_boxCollider->ColliderUpdate(
		m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
		m_playerSpring->GetRotQua());

	//	変数のリセット
	m_isGoal = false;
	m_isDead = false;
}
/// <summary>
/// データの保存
/// </summary>
void Player::SaveData()
{
	//	ばねデータの保存
	m_playerSpring->SaveData();
}