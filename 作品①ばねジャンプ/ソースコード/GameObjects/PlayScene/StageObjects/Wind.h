//--------------------------------------------------------------------------------------
// File: Wind.h
//
// 風クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef WIND_DEFINED
#define WIND_DEFINED

#include "GameObjects/PlayScene/StageObjects/IStageObject.h"

class Player;
class Particle;

/// <summary>
/// 風クラス
/// </summary>
class Wind : public IStageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	/// <param name="power">風力</param>
	Wind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Wind();

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
	void Reset() override;

	/// <summary>
	/// 風の向きの取得
	/// </summary>
	/// <returns>風の向き</returns>
	const DirectX::SimpleMath::Vector3 GetVector() { return m_vector; }
	/// <summary>
	/// 風力の取得
	/// </summary>
	/// <returns>風力</returns>
	const float GetPower() { return m_power; }

	/// <summary>
	/// プレイヤーの設定
	/// </summary>
	/// <param name="player">プレイヤークラスのポインタ</param>
	void SetPlayer(Player* player) { m_player = player; }

public:
	//	データアクセス用文字列
	static const std::string POWER_STR;

private:
	//	風の方向
	DirectX::SimpleMath::Vector3 m_vector;
	//	風力
	float m_power;

	//	風の衝突判定
	bool m_isHit;

	//	プレイヤークラスのポインタ
	Player* m_player;

	//	風パーティクルクラスのユニークポインタ
	std::unique_ptr<Particle> m_windParticle;
};
#endif // !WIND_DEFINED