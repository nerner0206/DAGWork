//--------------------------------------------------------------------------------------
// File: PlayerSpring.h
//
// プレイヤーばねクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_SPRING_DEFINED
#define PLAYER_SPRING_DEFINED

#include "Player.h"
#include "SpringState/SpringState.h"
#include "MyLib/JsonManager.h"

class SpringPart;
class PredictionLine;
class Balloon;

/// <summary>
/// プレイヤーばねクラス
/// </summary>
class PlayerSpring : public PlayerComponent
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="p">プレイヤークラスのポインタ</param>
	PlayerSpring(Player* p);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerSpring();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	/// <param name="stageObjects">ステージ管理クラスのポインタ</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		StageManager* stageManager) override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
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
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	void Reset(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;
	/// <summary>
	/// データの保存
	/// </summary>
	void SaveData() override;

	/// <summary>
	/// テスト更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void TestUpdate(const float& elapsedTime);

	/// <summary>
	/// 次の状態の設定
	/// </summary>
	/// <param name="state">ばね状態クラスのポインタ</param>
	void SetNextState(SpringState* state);

	/// <summary>
	///	風船の破壊
	/// </summary>
	void BreakBalloon();

	/// <summary>
	/// 速度の取得
	/// </summary>
	/// <returns>速度ベクトル</returns>
	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }
	/// <summary>
	/// 速度の設定
	/// </summary>
	/// <param name="vel">速度ベクトル</param>
	void SetVelocity(const DirectX::SimpleMath::Vector3& vel) { m_velocity = vel; }
	/// <summary>
	/// 速度の加算
	/// </summary>
	/// <param name="vel">速度ベクトル</param>
	void AddVelocity(const DirectX::SimpleMath::Vector3& vel) { m_velocity += vel; }

	/// <summary>
	/// 縮み中の取得
	/// </summary>
	/// <returns>縮み中</returns>
	const bool GetIsShrink() { return m_isShrink; }
	/// <summary>
	/// 縮み中の設定
	/// </summary>
	/// <param name="isShrink">縮み中</param>
	void SetIsShrink(const bool& isShrink) { m_isShrink = isShrink; }

	/// <summary>
	/// 重力の取得
	/// </summary>
	/// <returns>重力</returns>
	const float GetGravity() { return m_gravity; }
	/// <summary>
	/// ジャンプ力の取得
	/// </summary>
	/// <returns>ジャンプ力</returns>
	const float GetJumpForce() { return m_jumpForce; }

	/// <summary>
	/// 縮む変化率の取得
	/// </summary>
	/// <returns>縮む変化率</returns>
	const float GetShrinkRatio() { return m_shrinkRatio; }
	/// <summary>
	/// 伸びる速度の取得
	/// </summary>
	/// <returns>伸びる速度</returns>
	const float GetExtendSpeed() { return m_extendSpeed; }

	/// <summary>
	/// ゴール判定の取得
	/// </summary>
	/// <returns>ゴール判定</returns>
	const bool GetIsGoal() { return m_isGoal; }
	/// <summary>
	/// ゴール判定の設定
	/// </summary>
	/// <param name="isGoal">ゴール判定</param>
	void SetIsGoal(const bool& isGoal) { m_isGoal = isGoal; }

public:
	//	データの数
	static const int DATA_NUMBER = 5;
	//	データアクセス文字列配列
	static const std::string DATA_STRING[DATA_NUMBER];

	//	当たり判定の半径
	static const float COLLISION_RADIUS;
	//	球の当たり判定の座標
	static const DirectX::SimpleMath::Vector3 COLLISION_POSITION_OFFSET;
	//	頭の座標
	static const DirectX::SimpleMath::Vector3 HEAD_POSITION_OFFSET;

private:
	//	jsonファイル
	nlohmann::json m_springData;

	//	プレイヤー頭クラスのユニークポインタ
	std::unique_ptr<PlayerComponent> m_head;

	//	ばね状態クラスのポインタ
	SpringState* m_nowSpringState;
	//	次のばね状態クラスのポインタ
	SpringState* m_nextSpringState;

	//	速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//	縮み中
	bool m_isShrink;

	//	重力
	float m_gravity;
	//	ジャンプ力
	float m_jumpForce;

	//	縮む変化率
	float m_shrinkRatio;
	//	伸びる速度
	float m_extendSpeed;

	//	横の力
	float m_XZForceRatio;

	//	前フレームのマウス座標
	DirectX::SimpleMath::Vector2 m_oldMousePos;

	//	接触した風船
	Balloon* m_hitBalloon;

	//	ばねのパーツのユニークポインタ配列
	std::vector<std::unique_ptr<SpringPart>> m_springParts;

	//	衝突位置
	DirectX::SimpleMath::Vector3 m_hitPos;

	//	ゴール判定
	bool m_isGoal;

	//	予測線クラスのユニークポインタ
	std::unique_ptr<PredictionLine> m_line;

private:
	/// <summary>
	/// 状態の設定
	/// </summary>
	/// <param name="state">ばね状態クラスのポインタ</param>
	void SetState(SpringState* state);
	/// <summary>
	/// 状態の削除
	/// </summary>
	void DeleteState();

	/// <summary>
	/// 回転更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void RotUpdate(const float& elapsedTime);
	/// <summary>
	/// めり込み補正
	/// </summary>
	/// <param name="distance">めり込み量</param>
	/// <returns>補正ベクトル</returns>
	DirectX::SimpleMath::Vector3 InImmersed(const float& distance);

	/// <summary>
	/// 予測線表示の切り替え
	/// </summary>
	void ChangeDisplayLine();
	/// <summary>
	///	予測線の計算
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void PreLine(const float& elapsedTime);
};
#endif // !PLAYER_SPRING_DEFINED