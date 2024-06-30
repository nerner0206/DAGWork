//--------------------------------------------------------------------------------------
// File: Result.h
//
// リザルト状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef RESULT_DEFINED
#define RESULT_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class Particle;
class SpaceUI;
class CounterUI;

class Result : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	/// <param name="resultTime">結果時間</param>
	Result(PlayScene* scene, PlayCamera* camera, const float& resultTime);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Result();

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
	//	時間UIの座標
	static const DirectX::SimpleMath::Vector2 COUNTER_POSITION;

private:
	//	紙吹雪パーティクル
	std::unique_ptr<Particle> m_confettiParticle;

	//	リザルトUIのユニークポインタ
	std::unique_ptr<UserInterface> m_resultUI;

	//	スペースUIのユニークポインタ
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	カウンターUIのユニークポインタ
	std::unique_ptr<CounterUI> m_counterUI;

	//	カウンター
	int m_resultTime;
};
#endif // !RESULT_DEFINED
