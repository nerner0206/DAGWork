//--------------------------------------------------------------------------------------
// File: PredictionLine.h
//
// 予測線クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PREDICTION_LINE_DEFINED
#define PREDICTION_LINE_DEFINED

#include "GameObjects/Object.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

/// <summary>
/// 予測線クラス
/// </summary>
class PredictionLine
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PredictionLine();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PredictionLine();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset ();

	/// <summary>
	/// 座標の追加
	/// </summary>
	/// <param name="pos">座標</param>
	void AddPosition(const DirectX::SimpleMath::Vector3& pos) { m_poses.push_back(pos); }

	/// <summary>
	/// アクティブ状態の設定
	/// </summary>
	/// <param name="flag">アクティブ状態</param>
	void SetIsActive(const bool& flag) { m_isActive = flag; }
	/// <summary>
	/// アクティブ状態の取得
	/// </summary>
	/// <returns>アクティブ状態</returns>
	const bool GetIsActive() { return m_isActive; }

public:
	static const float PREDICTION_TIME;

private:
	//  頂点の初期位置とテクスチャUVの定数
	const static DirectX::VertexPositionTexture VERTICES[4];

	// 入力レイアウトのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル のコムポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// エフェクト のユニークポインタ
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// プリミティブバッチ のユニークポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//	パーティクルごとの座標
	std::vector<DirectX::SimpleMath::Vector3> m_poses;
	//	アクティブ状態
	bool m_isActive;
};
#endif // !JUMP_PARTICLE_DEFINED
