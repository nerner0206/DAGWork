//--------------------------------------------------------------------------------------
// File: Goal.h
//
// ゴールクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GOAL_DEFINED
#define GOAL_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"

/// <summary>
/// ゴールクラス
/// </summary>
class Goal : public Ground
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	Goal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goal();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugRender() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;
};
#endif // !GOAL_DEFINED