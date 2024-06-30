//--------------------------------------------------------------------------------------
// File: Particle.h
//
// パーティクル基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PARTICLE_DEFINED
#define PARTICLE_DEFINED

#include "GameObjects/Object.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

/// <summary>
/// パーティクル基底クラス
/// </summary>
class Particle : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="sca">拡大率</param>
	Particle(const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& sca) :
		Object(pos, rot, sca),
		m_isActive(false)
	{

	}

	/// <summary>
	/// アクティブ状態の取得
	/// </summary>
	/// <returns>アクティブ状態</returns>
	const bool& GetActive() { return m_isActive; }
	/// <summary>
	/// アクティブ状態の設定
	/// </summary>
	/// <param name="flag">アクティブ状態</param>
	void SetActive(const bool& flag) { m_isActive = flag; }
	
public:
	/// <summary>
	///	デストラクタ
	/// </summary>
	virtual ~Particle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	///	描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// パーティクルの実行
	/// </summary>
	/// <param name="pos">座標</param>
	virtual void Play(const DirectX::SimpleMath::Vector3& pos) = 0;
	/// <summary>
	/// パーティクルの停止
	/// </summary>
	virtual void Stop() = 0;

private:
	//	アクティブ状態
	bool m_isActive;
};
#endif // !PARTICLE_DEFINED

