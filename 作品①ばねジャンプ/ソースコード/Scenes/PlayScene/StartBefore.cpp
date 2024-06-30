//--------------------------------------------------------------------------------------
// File: StartBefore.cpp
//
// 開始前状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StartBefore.h"

#include "Scenes/PlayScene/GameStart.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

using namespace DirectX;

//	カメラ速度
const float StartBefore::CAMERA_SPEED = 14.03f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">プレイシーンクラスのポインタ</param>
/// <param name="camera">プレイカメラクラスのポインタ</param>
StartBefore::StartBefore(PlayScene* scene, PlayCamera* camera) :
    IPlaySceneState(scene, camera),
    m_time(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
StartBefore::~StartBefore()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void StartBefore::Initialize(Player* player, StageManager* stageManager)
{
    //	スタート座標の取得
    m_startPos = stageManager->GetStartPosition();
    //	ゴール座標の取得
    m_goalPos= stageManager->GetGoal()->GetPos();

    //  距離の計算
    float distance = (m_startPos - m_goalPos).Length();
    //  時間の計算
    m_time = distance / CAMERA_SPEED;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="stageManager">ステージ管理クラスのポインタ</param>
void StartBefore::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
    SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
    //	カーソル座標を戻す
    SetCursorPos(centerPos.x, centerPos.y);

    //  カメラの更新
    bool finish = GetPlayCamera()->BeforeUpdate(
        elapsedTime,
        m_startPos,
        m_goalPos,
        m_time);

    //	ステージマネージャーの更新
    stageManager->Update(elapsedTime);

    if (finish)
    {
        //	セレクトシーンへ
        GetPlayScene()->SetNextState(new GameStart(GetPlayScene(), GetPlayCamera()));
        //	処理しない
        return;
    }
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void StartBefore::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    
}

/// <summary>
/// 終了
/// </summary>
void StartBefore::Finalize()
{

}