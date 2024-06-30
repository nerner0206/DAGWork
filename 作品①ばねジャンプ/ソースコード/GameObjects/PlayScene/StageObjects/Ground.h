//--------------------------------------------------------------------------------------
// File: Ground.h
//
// 足場クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GROUND_DEFINED
#define GROUND_DEFINED

#include "GameObjects/PlayScene/StageObjects/IStageObject.h"

/// <summary>
/// 足場クラス
/// </summary>
class Ground : public IStageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	Ground(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground();

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
	/// 揺れ判定の設定
	/// </summary>
	/// <param name="flag">揺れ判定</param>
	void SetIsShake(const bool& flag) { m_isShake = flag; }

public:
	/// <summary>
	///	揺れる
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Shaking(const float& elapsedTime);

private:
	//	デフォルト拡大率
	DirectX::SimpleMath::Vector3 m_defSca;
	//	雲の揺れ拡大率
	DirectX::SimpleMath::Vector3 m_targetSca;

	//	雲の揺れ判定
	bool m_isShake;
	//	タイマー
	float m_t;
};
#endif // !GROUND_DEFINED