//--------------------------------------------------------------------------------------
// File: ConfettiParticle.h
//
// 紙吹雪パーティクルクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef CONFETTI_PARTICLE_DEFINED
#define CONFETTI_PARTICLE_DEFINED

#include "Particle.h"

/// <summary>
/// 紙吹雪パーティクルクラス
/// </summary>
class ConfettiParticle : public Particle
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ConfettiParticle();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ConfettiParticle();

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
	const static int PARTICLE_NUMBER = 255;

	//	座標の上限値
	static const float MAX_POSITION;

private:
	// 入力レイアウトのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル のコムポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// エフェクト のユニークポインタ
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// プリミティブバッチ のユニークポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//	パーティクルごとの座標
	std::vector<DirectX::SimpleMath::Vector3> m_particlePos;
	//	パーティクルのごとのY速度
	std::vector<float> m_particleVel_Y;
	//	パーティクルごとの色
	std::vector<DirectX::SimpleMath::Vector4> m_particleColor;
};
#endif // !JUMP_PARTICLE_DEFINED
