//--------------------------------------------------------------------------------------
// File: Result.cpp
//
// リザルト状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Result.h"

#include "Scenes/SelectScene.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/PlayScene/Particle/ConfettiParticle.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	時間UIの座標
const SimpleMath::Vector2 Result::COUNTER_POSITION = SimpleMath::Vector2(640, 400);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
/// <param name="proj">射影行列</param>
Result::Result(PlayScene* scene, PlayCamera* camera, const float& resultTime) :
	IPlaySceneState(scene, camera),
	m_resultTime((int)resultTime)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Result::~Result()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void Result::Initialize(Player* player, StageManager* stageManager)
{
	//	パーティクルの生成
	m_confettiParticle = std::make_unique<ConfettiParticle>();
	m_confettiParticle->Initialize();

	//	パーティクルの発射
	m_confettiParticle->Play(stageManager->GetGoal()->GetPos());
	//	パーティクルの追加
	GetPlayScene()->AddParticle(m_confettiParticle.get());

	//	クリア音の再生
	GetAudioResources()->PlayClearSE();

	//  リザルトUIの生成
	m_resultUI = std::make_unique<UserInterface>();
	m_resultUI->Create(
		DataPath::RESULT_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT) / 2,
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//  スペースUIの生成
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

	//	カウンターUIの生成
	m_counterUI = std::make_unique<CounterUI>();
	m_counterUI->Initialize(COUNTER_POSITION);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void Result::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	キーボードを設定
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	スペースを押したらセレクトシーンへ
	if (kbTracker->pressed.Space)
	{
		//  決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	セレクトシーンへ
		GetPlayScene()->GetSceneManager()->SetNextScene(new SelectScene());
		//	処理しない
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Result::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_resultUI->Render();

	//  スペースUIの描画
	m_spaceUI->Render();
	//	カウンターの描画
	m_counterUI->Render(m_resultTime);
}

/// <summary>
/// 終了
/// </summary>
void Result::Finalize()
{

}