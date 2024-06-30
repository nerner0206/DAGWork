//--------------------------------------------------------------------------------------
// File: InGame.cpp
//
// ゲーム中状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "InGame.h"

#include "Scenes/PlayScene/Dead.h"
#include "Scenes/PlayScene/Result.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	UIの拡大率
const float InGame::UI_SCALE = 0.5f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
InGame::InGame(PlayScene* scene, PlayCamera* camera) :
	IPlaySceneState(scene, camera),
	m_timer(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
InGame::~InGame()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void InGame::Initialize(Player* player, StageManager* stageManager)
{
	//  XアイコンUIの生成
	m_X_IconUI = std::make_unique<UserInterface>();
	m_X_IconUI->Create(
		DataPath::X_ICON_IMAGE_PATH,
		SimpleMath::Vector2(X_ICON_X, ICON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  XボタンUIの生成
	m_X_ButtonUI = std::make_unique<UserInterface>();
	m_X_ButtonUI->Create(
		DataPath::X_BUTTON_IMAGE_PATH,
		SimpleMath::Vector2(X_ICON_X + BUTTON_DISTANCE, BUTTON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  CアイコンUIの生成
	m_C_IconUI = std::make_unique<UserInterface>();
	m_C_IconUI->Create(
		DataPath::C_ICON_IMAGE_PATH,
		SimpleMath::Vector2(C_ICON_X, ICON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  CボタンUIの生成
	m_C_ButtonUI = std::make_unique<UserInterface>();
	m_C_ButtonUI->Create(
		DataPath::C_BUTTON_IMAGE_PATH,
		SimpleMath::Vector2(C_ICON_X + BUTTON_DISTANCE, BUTTON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//	カウンターUIの生成
	m_counterUI = std::make_unique<CounterUI>();
	m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

	//	プレイヤーのリセット
	player->Reset();

	//	タイマーの初期化
	m_timer = 0.0f;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void InGame::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	プレイ時間を増やす
	m_timer += elapsedTime;

	//	ステージマネージャーの更新
	stageManager->Update(elapsedTime);
	//	プレイヤーの更新
	player->Update(elapsedTime, stageManager);

	//	カメラの更新
	GetPlayCamera()->Update(elapsedTime, player);

	//	ゴール判定
	if (player->GetIsGoal())
	{
		//	リザルト状態にする
		GetPlayScene()->SetNextState(new Result(GetPlayScene(), GetPlayCamera(), m_timer));
		return;
	}

	//	死亡判定
	if (player->GetIsDead())
	{
		//	死亡状態にする
		GetPlayScene()->SetNextState(new Dead(GetPlayScene(), GetPlayCamera()));
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void InGame::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	UIの描画
	m_C_IconUI->Render();
	m_C_ButtonUI->Render();
	m_X_IconUI->Render();
	m_X_ButtonUI->Render();

	//	カウンターの描画
	m_counterUI->Render((int)m_timer);
}

/// <summary>
/// 終了
/// </summary>
void InGame::Finalize()
{

}