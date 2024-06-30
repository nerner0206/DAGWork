//--------------------------------------------------------------------------------------
// File: InputWait.h
//
// 入力待機状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef INPUT_WAIT_DEFINED
#define INPUT_WAIT_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class SpaceUI;
class CounterUI;

/// <summary>
/// 入力待機状態クラス
/// </summary>
class InputWait : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	InputWait(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~InputWait();

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
	//	スペースUIのユニークポインタ
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	カウンターUIのユニークポインタ
	std::unique_ptr<CounterUI> m_counterUI;
};
#endif // !INPUT_WAIT_DEFINED
