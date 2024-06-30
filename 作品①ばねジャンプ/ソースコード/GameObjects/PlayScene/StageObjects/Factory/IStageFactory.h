//--------------------------------------------------------------------------------------
// File: IStageFactory.h
//
// ステージファクトリー基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISTAGE_FACTORY_DEFINED
#define ISTAGE_FACTORY_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"
#include "GameObjects/PlayScene/StageObjects/Goal.h"
#include "GameObjects/PlayScene/StageObjects/MoveGround.h"
#include "GameObjects/PlayScene/StageObjects/Balloon.h"
#include "GameObjects/PlayScene/StageObjects/Wind.h"

/// <summary>
/// ステージファクトリー基底クラス
/// </summary>
class IStageFactory
{
public:
	/// <summary>
	/// ゴールの生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>ゴールクラスのユニークポインタ</returns>
	virtual std::unique_ptr<Goal> CreateGoal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;

	/// <summary>
	/// 足場の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>足場クラスのポインタ</returns>
	virtual Ground* CreateGround(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;

	/// <summary>
	/// 動く足場の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="speed">移動速度</param>
	/// <returns>動く足場クラスのポインタ</returns>
	virtual MoveGround* CreateMoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed) = 0;

	/// <summary>
	/// 風の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="power">風力</param>
	/// <returns>風クラスのポインタ</returns>
	virtual std::unique_ptr<Wind> CreateWind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power) = 0;

	/// <summary>
	/// 風船の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>風船クラスのポインタ</returns>
	virtual Balloon* CreateBalloon(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;
};
#endif // !ISTAGE_FACTORY_DEFINED
