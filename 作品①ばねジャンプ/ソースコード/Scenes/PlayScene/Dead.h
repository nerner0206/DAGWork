//--------------------------------------------------------------------------------------
// File: Dead.h
//
// 死亡状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DEAD_DEFINED
#define DEAD_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class Dead : public IPlaySceneState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">プレイシーンクラスのポインタ</param>
	/// <param name="camera">プレイカメラクラスのポインタ</param>
	Dead(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Dead();

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
	//	死亡UIの拡大率
	static const float DEAD_SCALE;

private:
	//	死亡UIのユニークポインタ
	std::unique_ptr<UserInterface> m_deadUI;
	//	黒丸UIのユニークポインタ
	std::unique_ptr<UserInterface> m_blackUI;

	//	初期化フラグ
	bool m_init;
	//	時間
	float m_timer;
};
#endif // !DEAD_DEFINED
