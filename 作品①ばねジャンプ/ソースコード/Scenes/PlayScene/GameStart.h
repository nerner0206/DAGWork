//--------------------------------------------------------------------------------------
// File: GameStart.h
//
// ゲーム開始状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GAMEStart_DEFINED
#define GAMEStart_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class SpaceUI;
class CounterUI;

/// <summary>
/// ゲーム開始状態クラス
/// </summary>
class GameStart : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	GameStart(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStart();

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
	//	ルールUIの座標
	static const DirectX::SimpleMath::Vector2 RULU_POSITION;

private:
	//	ルール画像
	std::unique_ptr<UserInterface> m_ruluUI;

	//	スペースUIのユニークポインタ
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	カウンターUIのユニークポインタ
	std::unique_ptr<CounterUI> m_counterUI;
};
#endif // !IGAMEStart_DEFINED
