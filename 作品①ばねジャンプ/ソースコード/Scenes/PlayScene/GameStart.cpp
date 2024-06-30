//--------------------------------------------------------------------------------------
// File: GameStart.cpp
//
// ゲーム開始状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "GameStart.h"

#include "Scenes/PlayScene/InGame.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	ルールUIの座標
const SimpleMath::Vector2 GameStart::RULU_POSITION = SimpleMath::Vector2(30, 30);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
GameStart::GameStart(PlayScene* scene, PlayCamera* camera):
    IPlaySceneState(scene, camera)
{

}

/// <summary>
/// デストラクタ
/// </summary>
GameStart::~GameStart()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void GameStart::Initialize(Player* player, StageManager* stageManager)
{
    //  ルールUIの生成
    m_ruluUI = std::make_unique<UserInterface>();
    m_ruluUI->Create(
        DataPath::RULU_IMAGE_PATH,
        RULU_POSITION,
        SimpleMath::Vector2::One,
        ANCHOR::TOP_LEFT);

    //  スペースUIの生成
    m_spaceUI = std::make_unique<SpaceUI>();
    m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

    //	カウンターUIの生成
    m_counterUI = std::make_unique<CounterUI>();
    m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

    //	プレイヤーのリセット
    player->Reset();

    //	カメラの更新
    GetPlayCamera()->Update(0.0f, player);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void GameStart::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	キーボードの取得
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	スペースを押したらセレクトシーンへ
	if (kbTracker->pressed.Space && GetPlayScene()->GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
        //  決定音の再生
        GetAudioResources()->PlayDecideSE();
		//	ゲーム中へ
		GetPlayScene()->SetNextState(new InGame(GetPlayScene(), GetPlayCamera()));
		//	処理しない
		return;
	}

    //	ステージマネージャーの更新
    stageManager->Update(elapsedTime);

    //  プレイヤーばねクラスにキャスト
    PlayerSpring* spring = dynamic_cast<PlayerSpring*>(player->GetPlayerSpring());
    //  回転の更新
    spring->TestUpdate(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void GameStart::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    //  ルールUIの描画
    m_ruluUI->Render();

    //  スペースUIの描画
    m_spaceUI->Render();
    //	カウンターの描画
    m_counterUI->Render(0);
}

/// <summary>
/// 終了
/// </summary>
void GameStart::Finalize()
{
    
}