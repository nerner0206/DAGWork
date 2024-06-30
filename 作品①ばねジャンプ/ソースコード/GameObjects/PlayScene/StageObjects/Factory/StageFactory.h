//--------------------------------------------------------------------------------------
// File: StageFactory.h
//
// ステージファクトリークラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef STAGE_FACTORY_DEFINED
#define STAGE_FACTORY_DEFINED

#include "GameObjects/PlayScene/StageObjects/Factory/IStageFactory.h"

class StageFactory : public IStageFactory
{
public:
	/// <summary>
	/// ゴールの生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>ゴールクラスのユニークポインタ</returns>
	static std::unique_ptr<Goal> CreateGoal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);

	/// <summary>
	/// 足場の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>足場クラスのポインタ</returns>
	static Ground* CreateGround(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);

	/// <summary>
	/// 動く足場の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="speed">移動速度</param>
	/// <returns>動く足場クラスのポインタ</returns>
	static MoveGround* CreateMoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed);

	/// <summary>
	/// 風の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="power">風力</param>
	/// <returns>風クラスのポインタ</returns>
	static std::unique_ptr<Wind> CreateWind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power);

	/// <summary>
	/// 風船の生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <returns>風船クラスのポインタ</returns>
	static Balloon* CreateBalloon(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
};
#endif // !STAGE_FACTORY_DEFINED
