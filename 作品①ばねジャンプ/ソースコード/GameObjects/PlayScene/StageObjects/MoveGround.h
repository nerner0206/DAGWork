//--------------------------------------------------------------------------------------
// File: MoveGround.h
//
// 動く足場クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef MOVE_GROUND_DEFINED
#define MOVE_GROUND_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"

/// <summary>
/// 動く足場クラス
/// </summary>
class MoveGround : public Ground
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="speed">速度</param>
	MoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveGround();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugRender() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// リセット
	/// </summary>
	void Reset() override;

	/// <summary>
	/// 速度の取得
	/// </summary>
	/// <returns>速度</returns>
	const float GetSpeed() { return m_speed; }

public:
	//	データアクセス用文字列
	static const std::string POSITIONS_STR;
	//	データアクセス用文字列
	static const std::string SPEED_STR;

private:
	//	移動先座標
	std::vector<DirectX::SimpleMath::Vector3> m_poses;

	//	速度
	float m_speed;

	//	座標番号
	int m_num;
	//	次の番号
	int m_nextNum;

	//	目標時間
	float m_time;
	//	タイマー
	float m_timer;
};
#endif // !MOVE_GROUND_DEFINED