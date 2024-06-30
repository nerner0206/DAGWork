//--------------------------------------------------------------------------------------
// File: StartBefore.h
//
// 開始前状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef START_BEFORE_DEFINED
#define START_BEFORE_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

/// <summary>
/// 開始前状態クラス
/// </summary>
class StartBefore : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	StartBefore(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~StartBefore();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤークラスのポインタ</param>
	/// <param name="stageManager">ステージ管理クラスのポインタ</param>
	void Initialize(Player* player, StageManager* stageManager) override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="player">プレイヤークラスのポインタ</param>
	/// <param name="stageManager">ステージ管理クラスのポインタ</param>
	void Update(const float& elapsedTime, Player* player, StageManager* stageManager) override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

private:
	//	カメラ速度
	static const float CAMERA_SPEED;

private:
	//	スタート座標
	DirectX::SimpleMath::Vector3 m_startPos;
	//	ゴール座標
	DirectX::SimpleMath::Vector3 m_goalPos;

	//	移動時間
	float m_time;
};
#endif // !INPUT_WAIT_DEFINED
