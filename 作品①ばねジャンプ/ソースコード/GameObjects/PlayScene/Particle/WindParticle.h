//--------------------------------------------------------------------------------------
// File: WindParticle.h
//
// 風パーティクルクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef WIND_PARTICLE_DEFINED
#define WIND_PARTICLE_DEFINED

#include "Particle.h"

class Wind;

/// <summary>
/// 風パーティクルクラス
/// </summary>
class WindParticle : public Particle
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="wind">風クラスのポインタ</param>
	WindParticle(Wind* wind);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WindParticle();

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
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// パーティクルの実行
	/// </summary>
	/// <param name="pos">座標</param>
	void Play(const DirectX::SimpleMath::Vector3& pos) override;
	/// <summary>
	/// パーティクルの停止
	/// </summary>
	void Stop() override;

private:
	//  頂点の初期位置とテクスチャUVの定数
	const static DirectX::VertexPositionTexture VERTICES[4];
	//	パーティクルの数
	const static int PARTICLE_NUMBER = 16;

	// 入力レイアウトのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル のコムポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// エフェクト のユニークポインタ
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// プリミティブバッチ のユニークポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//	パーティクルごとの座標
	std::vector<DirectX::SimpleMath::Vector3> m_particlePos;
	//	パーティクルごとの座標
	std::vector<DirectX::SimpleMath::Vector3> m_particleStartPos;

	//  タイマー
	float m_timer;

	//	風クラスのポインタ
	Wind* m_wind;
};
#endif // !CLOUD_PARTICLE_DEFINED
