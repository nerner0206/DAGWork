//--------------------------------------------------------------------------------------
// File: Dead.cpp
//
// 死亡状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Dead.h"

#include "Scenes/PlayScene/InputWait.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

using namespace DirectX;

//	死亡UIの拡大率
const float Dead::DEAD_SCALE = 7.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
Dead::Dead(PlayScene* scene, PlayCamera* camera):
	IPlaySceneState(scene, camera),
	m_timer(0.0f),
	m_init(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Dead::~Dead()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void Dead::Initialize(Player* player, StageManager* stageManager)
{
	//	死亡音の再生
	GetAudioResources()->PlayDeadSE();

	//	死亡UIの生成
	m_deadUI = std::make_unique<UserInterface>();
	m_deadUI->Create(
		DataPath::DEAD_ICON_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, UserResources::WINDOW_HEIGHT / 2),
		SimpleMath::Vector2::Zero,
		ANCHOR::MIDDLE_CENTER);

	//	黒丸UIの生成
	m_blackUI = std::make_unique<UserInterface>();
	m_blackUI->Create(
		DataPath::BLACK_CIRCLE_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, UserResources::WINDOW_HEIGHT / 2),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//	タイマーの初期化
	m_timer = 0.0f;
	//	初期化フラグ
	m_init = false;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void Dead::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	時間を増やす
	m_timer += elapsedTime;

	if (!m_init)
	{
		//	拡大率の計算
		SimpleMath::Vector2 sca = SimpleMath::Vector2::Lerp(
			SimpleMath::Vector2::Zero,
			SimpleMath::Vector2::One * DEAD_SCALE,
			m_timer);

		//	拡大率の設定
		m_deadUI->SetScale(sca);

		//	一秒経過していない場合、処理しない
		if (m_timer < 1.0f) return;

		//	初期化
		m_init = true;
		//	タイマーの初期化
		m_timer = 0.0f;

		//	リセット
		player->Reset();
		stageManager->Reset();

		//	カメラの更新
		GetPlayCamera()->Update(elapsedTime, player);

		return;
	}

	//	拡大率の計算(倍速)
	SimpleMath::Vector2 sca = SimpleMath::Vector2::Lerp(
		SimpleMath::Vector2::One,
		SimpleMath::Vector2::Zero,
		m_timer * 2.0f);

	//	拡大率の設定
	m_blackUI->SetScale(sca);

	//	0.5秒後、入力待機状態にする
	if(m_timer >= 0.5f) GetPlayScene()->SetNextState(new InputWait(GetPlayScene(), GetPlayCamera()));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Dead::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	1秒以下
	if (!m_init) m_deadUI->Render();
	else m_blackUI->Render();
}

/// <summary>
/// 終了
/// </summary>
void Dead::Finalize()
{
	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
	//	カーソル座標を戻す
	SetCursorPos(centerPos.x, centerPos.y);
}