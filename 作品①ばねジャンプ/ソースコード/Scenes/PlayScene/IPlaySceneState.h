//--------------------------------------------------------------------------------------
// File: IPlaySceneState.h
//
// プレイシーンの状態遷移基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef IPLAY_SCENE_STATE_DEFINED
#define IPLAY_SCENE_STATE_DEFINED

#include "Scenes/PlayScene.h"

#include "Game/DataPath.h"

/// <summary>
/// プレイシーンの状態遷移基底クラス
/// </summary>
class IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	IPlaySceneState(PlayScene* scene, PlayCamera* camera) :
		m_playScene(scene),
		m_playCamera(camera),
		m_ur(UserResources::GetInstance()),
		m_ar(AudioResources::GetInstance()) { }

	/// <summary>
	/// ユーザーリソースの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	UserResources* GetUserResources() { return m_ur; }
	/// <summary>
	/// ユーザーリソースの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// プレイシーンの取得
	/// </summary>
	/// <returns>プレイシーンクラスのポインタ</returns>
	PlayScene* GetPlayScene() { return m_playScene; }
	/// <summary>
	/// プレイカメラの取得
	/// </summary>
	/// <returns>プレイカメラクラスのポインタ</returns>
	PlayCamera* GetPlayCamera() { return m_playCamera; }

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IPlaySceneState() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤークラスのポインタ</param>
	/// <param name="stageManager">ステージ管理クラスのポインタ</param>
	virtual void Initialize(Player* player, StageManager* stageManager) = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="player">プレイヤークラスのポインタ</param>
	/// <param name="stageManager">ステージ管理クラスのポインタ</param>
	virtual void Update(const float& elapsedTime, Player* player, StageManager* stageManager) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;

private:
	//	ユーザーリソースクラスのポインタ
	UserResources* m_ur;
	//	音リソースクラスのポインタ
	AudioResources* m_ar;

	//	プレイシーン
	PlayScene* m_playScene;

	//	プレイカメラ
	PlayCamera* m_playCamera;
};
#endif // !IPLAY_SCENE_STATE_DEFINED