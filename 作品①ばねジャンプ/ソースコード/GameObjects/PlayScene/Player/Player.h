//--------------------------------------------------------------------------------------
// File: Player.h
//
// プレイヤークラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

#include "PlayerComponent.h"

class Particle;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="startPos">初期座標</param>
	void Initialize(const DirectX::SimpleMath::Vector3& startPos);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="stageObjs">ステージ管理クラスのポインタ</param>
	void Update(const float& elapsedTime, StageManager* stageManager);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugRender();
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// リセットする
	/// </summary>
	void Reset();
	/// <summary>
	/// データの保存
	/// </summary>
	void SaveData();

	/// <summary>
	/// マウス感度の取得
	/// </summary>
	/// <returns>マウス感度</returns>
	const float GetMouseSensitivity() { return m_mouseSensitivity; }
	/// <summary>
	/// マウス感度の設定
	/// </summary>
	/// <param name="mouseSensitivity">マウス感度</param>
	void SetMouseSensitivity(const float& mouseSensitivity) { m_mouseSensitivity = mouseSensitivity; }

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns>当たり判定クラスのポインタ</returns>
	CollisionObject* GetBoxCollider() { return m_boxCollider.get(); }

	/// <summary>
	/// ばねのポインタの取得
	/// </summary>
	/// <returns>プレイヤー部品クラスのポインタ</returns>
	PlayerComponent* GetPlayerSpring() { return m_playerSpring.get(); }

	/// <summary>
	/// ゴール判定の取得
	/// </summary>
	/// <returns>ゴール判定フラグ</returns>
	const bool GetIsGoal() { return m_isGoal; }

	/// <summary>
	/// 死亡判定の設定
	/// </summary>
	/// <param name="flag">死亡判定フラグ</param>
	void SetIsDead(const bool& flag) { m_isDead = flag; }
	/// <summary>
	/// 死亡判定の取得
	/// </summary>
	/// <returns></returns>
	const bool GetIsDead() { return m_isDead; }

	/// <summary>
	/// ジャンプパーティクルの取得
	/// </summary>
	/// <returns>パーティクル基底クラスのポインタ</returns>
	Particle* GetJumpParticle() { return m_jumpParticle.get(); }
	/// <summary>
	/// 爆発パーティクルの取得
	/// </summary>
	/// <returns>パーティクル基底クラスのポインタ</returns>
	Particle* GetExplosionParticle() { return m_explosionParticle.get(); }

private:
	//	当たり判定のオフセット
	static const DirectX::SimpleMath::Vector3 COLLISION_POSITION_OFFSET;
	//	当たり判定の拡大率
	static const DirectX::SimpleMath::Vector3 COLLISION_SCALE;

private:
	//	プレイヤーばねクラスのユニークポインタ
	std::unique_ptr<PlayerComponent> m_playerSpring;
	//	プレイヤー全体の当たり判定クラスのユニークポインタ
	std::unique_ptr<CollisionObject> m_boxCollider;

	//	初期座標
	DirectX::SimpleMath::Vector3 m_startPos;

	//	マウス感度
	float m_mouseSensitivity;

	//	ゴール判定フラグ
	bool m_isGoal;
	//	死亡判定フラグ
	bool m_isDead;

	//	ジャンプパーティクルクラスのユニークポインタ
	std::unique_ptr<Particle> m_jumpParticle;
	//	爆発パーティクルクラスのユニークポインタ
	std::unique_ptr<Particle> m_explosionParticle;
};
#endif // !PLAYER_DEFINED