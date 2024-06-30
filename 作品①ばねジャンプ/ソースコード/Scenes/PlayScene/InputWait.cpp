//--------------------------------------------------------------------------------------
// File: InputWait.cpp
//
// 入力待機状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "InputWait.h"

#include "Scenes/PlayScene/InGame.h"

#include "GameObjects/PlayScene/Camera/PlayCamera.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
InputWait::InputWait(PlayScene* scene, PlayCamera* camera) :
    IPlaySceneState(scene, camera)
{

}

/// <summary>
/// デストラクタ
/// </summary>
InputWait::~InputWait()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void InputWait::Initialize(Player* player, StageManager* stageManager)
{
    //  スペースUIの生成
    m_spaceUI = std::make_unique<SpaceUI>();
    m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

    //	カウンターUIの生成
    m_counterUI = std::make_unique<CounterUI>();
    m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

    //	カメラの更新
    GetPlayCamera()->Update(0.0f, player);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void InputWait::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
    SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
    //	カーソル座標を戻す
    SetCursorPos(centerPos.x, centerPos.y);

	//	キーボードを設定
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	スペースを押したらセレクトシーンへ
	if (kbTracker->pressed.Space && GetPlayScene()->GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
        //  決定音の再生
        GetAudioResources()->PlayDecideSE();
		//	セレクトシーンへ
		GetPlayScene()->SetNextState(new InGame(GetPlayScene(), GetPlayCamera()));
		//	処理しない
		return;
	}

    //	ステージマネージャーの更新
    stageManager->Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void InputWait::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    //  スペースUIの描画
    m_spaceUI->Render();
    //	カウンターの描画
    m_counterUI->Render(0);
}

/// <summary>
/// 終了
/// </summary>
void InputWait::Finalize()
{

}