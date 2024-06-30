//--------------------------------------------------------------------------------------
// File: InGame.h
//
// ゲーム中状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef INGAME_DEFINED
#define INGAME_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class CounterUI;

class InGame : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	InGame(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~InGame();

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
	//	UIの拡大率
	static const float UI_SCALE;

	//	アイコンのY座標
	static const int ICON_Y = 715;
	//	ボタンのY座標
	static const int BUTTON_Y = 720;

	//	XボタンのX座標
	static const int X_ICON_X = 0;
	//	CボタンのX座標
	static const int C_ICON_X = 175;

	//	ボタンの距離
	static const int BUTTON_DISTANCE = 100;

private:
	//	Cアイコン・ボタンUIのユニークポインタ
	std::unique_ptr<UserInterface> m_C_IconUI;
	std::unique_ptr<UserInterface> m_C_ButtonUI;

	//	Xアイコン・ボタンUIのユニークポインタ
	std::unique_ptr<UserInterface> m_X_IconUI;
	std::unique_ptr<UserInterface> m_X_ButtonUI;

	//	カウンターUIのユニークポインタ
	std::unique_ptr<CounterUI> m_counterUI;
	//	タイマー
	float m_timer;
};
#endif // !INGAME_DEFINED
