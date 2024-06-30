//--------------------------------------------------------------------------------------
// File: PlayCamera.h
//
// プレイカメラクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAY_CAMERA_DEFINED
#define PLAY_CAMERA_DEFINED

#include "GameObjects/Common/Camera.h"
#include "MyLib/JsonManager.h"

class Player;

/// <summary>
/// プレイカメラクラス
/// </summary>
class PlayCamera : public Camera
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="startPos">開始座標</param>
	/// <param name="endPos">終了座標</param>
	PlayCamera(
		const DirectX::SimpleMath::Vector3& startPos,
		const DirectX::SimpleMath::Vector3& endPos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayCamera();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="player">プレイヤークラスのポインタ</param>
	void Update(const float& elapsedTime, Player* player);

	/// <summary>
	/// 開始前更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="startPos">開始座標</param>
	/// <param name="endPos">終了座標</param>
	/// <param name="duration">間隔</param>
	/// <returns>更新終了フラグ</returns>
	bool BeforeUpdate(
		const float& elapsedTime, 
		const DirectX::SimpleMath::Vector3& startPos, 
		const DirectX::SimpleMath::Vector3& endPos,
		const float& duration);

	/// <summary>
	/// デバッグ用描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void DebugRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// データの保存
	/// </summary>
	void SaveData();

private:
	//	データの数
	static const int DATA_NUMBER = 5;
	//	データアクセス文字列配列
	static const std::string DATA_STRING[DATA_NUMBER];

private:
	//	jsonファイル
	nlohmann::json m_cameraData;

	//	座標のオフセット
	DirectX::SimpleMath::Vector3 m_offset;

	//	X座標のオフセット最大値
	float m_maxOffset_x;

	//	Z座標のオフセット最大値
	float m_maxOffset_z;
	//	Z座標のオフセット最小値
	float m_minOffset_z;

	//	注視点の変更距離
	float m_targetDistance;

	//	変更フラグ
	bool m_swich;

	//	補間率
	float m_t;
	//	タイマー
	float m_timer;

private:
	/// <summary>
	/// 座標の更新
	/// </summary>
	/// <param name="pos">基準座標</param>
	/// <param name="t">時間</param>
	/// <returns>座標</returns>
	DirectX::SimpleMath::Vector3 EyeUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const float& t);

	/// <summary>
	/// 目標座標の更新
	/// </summary>
	/// <param name="pos">基準座標</param>
	/// <param name="forward">正面座標</param>
	/// <param name="t">時間</param>
	/// <returns>目標座標</returns>
	DirectX::SimpleMath::Vector3 TargetUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& forward,
		const float& t);

	/// <summary>
	/// オフセットの変更
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void ChangeOffset(const float& elapsedTime);
};
#endif // !PLAY_CAMERA_DEFINED