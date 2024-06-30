//--------------------------------------------------------------------------------------
// File: StageFactory.cpp
//
// ステージファクトリークラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StageFactory.h"

/// <summary>
/// ゴールの生成
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <returns>ゴールクラスのユニークポインタ</returns>
std::unique_ptr<Goal> StageFactory::CreateGoal(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	地面を作成
	std::unique_ptr<Goal> goal = std::make_unique<Goal>(pos, rot, sca);
	//	初期化
	goal->Initialize();
	//	渡す
	return std::move(goal);
}

/// <summary>
/// 足場の生成
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <returns>足場クラスのポインタ</returns>
Ground* StageFactory::CreateGround(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	地面を作成
	Ground* ground = new Ground(pos, rot, sca);
	//	初期化
	ground->Initialize();
	//	渡す
	return ground;
}

/// <summary>
/// 動く足場の生成
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <param name="speed">移動速度</param>
/// <returns>動く足場クラスのポインタ</returns>
MoveGround* StageFactory::CreateMoveGround(
	const std::vector<DirectX::SimpleMath::Vector3>& poses,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& speed)
{
	//	飛行機を作成
	MoveGround* moveGround = new MoveGround(poses, rot, sca, speed);
	//	初期化
	moveGround->Initialize();
	//	返す
	return moveGround;
}

/// <summary>
/// 風の生成
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <param name="power">風力</param>
/// <returns>風クラスのポインタ</returns>
std::unique_ptr<Wind> StageFactory::CreateWind(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& power)
{
	//	風を作成
	std::unique_ptr<Wind> wind = std::make_unique<Wind>(pos, rot, sca, power);
	//	初期化
	wind->Initialize();

	//	返す
	return std::move(wind);
}

/// <summary>
/// 風船の生成
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <returns>風船クラスのポインタ</returns>
Balloon* StageFactory::CreateBalloon(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	風船を作成
	Balloon* balloon = new Balloon(pos, rot, sca);
	//	初期化
	balloon->Initialize();
	//	渡す
	return balloon;
}