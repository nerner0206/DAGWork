//--------------------------------------------------------------------------------------
// File: PlayerComponent.h
//
// プレイヤー部品クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_COMPONENT_DEFINED
#define PLAYER_COMPONENT_DEFINED

#include "GameObjects/PlayScene/CollisionObjects/CollisionObject.h"

#include "imgui.h"

#include <vector>

class StageManager;
class Player;

/// <summary>
/// プレイヤー部品クラス
/// </summary>
class PlayerComponent : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤークラスのポインタ</param>
	PlayerComponent(Player* player) :
		Object(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One),
		m_player(player),
		m_parent(nullptr),
		m_child(nullptr),
		m_collision(nullptr)
	{

	}

	/// <summary>
	/// 親の取得
	/// </summary>
	/// <returns>プレイヤー部品クラスのポインタ</returns>
	PlayerComponent* GetParent() { return m_parent; }
	/// <summary>
	/// 親の設定
	/// </summary>
	/// <param name="parent">プレイヤー部品クラスのポインタ</param>
	void SetParent(PlayerComponent* parent) { m_parent = parent; }

	/// <summary>
	/// 子の取得
	/// </summary>
	/// <returns>プレイヤー部品クラスのポインタ</returns>
	PlayerComponent* GetChild() { return m_child; }
	/// <summary>
	/// 子の設定
	/// </summary>
	/// <param name="child">プレイヤー部品クラスのポインタ</param>
	void SetChild(PlayerComponent* child) { m_child = child; }

	/// <summary>
	///	球の当たり判定の取得
	/// </summary>
	/// <returns>当たり判定クラスのポインタ</returns>
	CollisionObject* GetCollisionObject() { return m_collision.get(); }
	/// <summary>
	/// 球の当たり判定の設定
	/// </summary>
	/// <param name="obj">当たり判定クラスのポインタ</param>
	void SetCollisionObject(std::unique_ptr<CollisionObject> obj) { m_collision = std::move(obj); }
	
	/// <summary>
	///	ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const DirectX::SimpleMath::Matrix GetWorldMatrix() { return m_world; }
	/// <summary>
	///	ワールド行列の設定
	/// </summary>
	/// <param name="world">ワールド行列</param>
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/// <summary>
	/// プレイヤーの取得
	/// </summary>
	/// <returns>プレイヤークラスのポインタ</returns>
	Player* GetPlayer() { return m_player; }

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual	~PlayerComponent() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	virtual void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	/// <param name="stageObjects">ステージ管理クラスのポインタ</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		StageManager* stageManager) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugRender() = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	virtual void Reset(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) = 0;

	/// <summary>
	/// データの保存
	/// </summary>
	virtual void SaveData() = 0;

private:
	//	プレイヤークラスのポインタ
	Player* m_player;

	//	親クラス
	PlayerComponent* m_parent;
	//	子クラス
	PlayerComponent* m_child;

	//	球の当たり判定
	std::unique_ptr<CollisionObject> m_collision;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
};
#endif		// PLAYER_COMPONENT_DEFINED