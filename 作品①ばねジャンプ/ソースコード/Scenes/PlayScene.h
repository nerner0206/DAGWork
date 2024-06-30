//--------------------------------------------------------------------------------------
// File: PlayScene.h
//
// プレイシーンクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED

#include "MyLib/IScene.h"

#include <vector>

class IPlaySceneState;

class Player;
class StageManager;

class PlayCamera;
class DebugCamera;

class BigCloud;
class Particle;

/// <summary>
/// プレイシーンクラス
/// </summary>
class PlayScene : public IScene
{
public:
	//	プレイシーンモード
	enum class PlaySceneMode
	{
		PlayMode = 0,
		DebugMode
	};

	//	スペースUIの座標
	static const DirectX::SimpleMath::Vector2 SPACE_POSITION;
	//	時間UIの座標
	static const DirectX::SimpleMath::Vector2 COUNTER_POSITION;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="num">ステージ番号</param>
	PlayScene(const int& stageNum);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayScene();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	void Initialize(const int& mouseNumber) override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// 描画
	/// </summary>
	void Render() override;
	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowRender() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// プレイシーン状態の設定
	/// </summary>
	/// <param name="state">プレイシーン状態クラスのポインタ</param>
	void SetState(IPlaySceneState* state);
	/// <summary>
	/// 次のプレイシーン状態の設定
	/// </summary>
	/// <param name="state">プレイシーン状態クラスのポインタ</param>
	void SetNextState(IPlaySceneState* state);

	/// <summary>
	/// プレイヤーの取得
	/// </summary>
	/// <returns>プレイヤークラスのポインタ</returns>
	Player* GetPlayer() { return m_player.get(); }

	/// <summary>
	/// パーティクルの追加
	/// </summary>
	/// <param name="particle">パーティクルクラスのポインタ</param>
	void AddParticle(Particle* particle) { m_particles.push_back(particle); }

	/// <summary>
	/// マウス感度の設定
	/// </summary>
	/// <param name="num">マウス感度</param>
	void SetMouseSpeed(const int& mouseNumber);

private:
	//	ライトの座標
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	//	ライトの影響範囲
	static const float LIGHT_RANGE;

	//	大きい雲の座標
	static const DirectX::SimpleMath::Vector3 BIG_CLOUD_POSITION;
	//	大きい雲の拡大率
	static const float BIG_CLOUD_SCALE;

	//	ステージUIの距離
	static const int STAGE_DISTANCE = 30;
	//	ステージ番号UIの拡大率
	static const float STAGE_NUMBER_SCALE;

private:
	//	現在のモード
	PlaySceneMode m_mode;

	//	現在のプレイシーン状態のポインタ
	IPlaySceneState* m_nowState;
	//	次のプレイシーン状態のポインタ
	IPlaySceneState* m_nextState;

	//	プレイヤークラスのユニークポインタ
	std::unique_ptr<Player> m_player;
	//	ステージ管理クラスのユニークポインタ
	std::unique_ptr<StageManager> m_stageManager;
	//	ステージ番号
	int m_stageNum;

	//	プレイシーンカメラクラスのユニークポインタ
	std::unique_ptr<PlayCamera> m_playCamera;
	//	デバッグカメラクラスのユニークポインタ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//	大きい雲クラスのユニークポインタ
	std::unique_ptr<BigCloud> m_bigCloud;

	//	パーティクルクラスのポインタ配列
	std::vector<Particle*> m_particles;

	//	ステージUIのユニークポインタ
	std::unique_ptr<UserInterface> m_stageUI;
	//	ステージ番号UIのユニークポインタ
	std::unique_ptr<UserInterface> m_stageNumUI;

private:
	/// <summary>
	/// プレイシーン状態の削除
	/// </summary>
	void DeletePlaySceneState();

	/// <summary>
	/// UIの生成
	/// </summary>
	void CreateUI();

	/// <summary>
	/// データの保存
	/// </summary>
	void SaveData();
};
#endif		// PLAY_SCENE_DEFINED