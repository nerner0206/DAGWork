//--------------------------------------------------------------------------------------
// File: JumpParticle.h
//
// ジャンプパーティクルクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef JUMP_PARTICLE_DEFINED
#define JUMP_PARTICLE_DEFINED

#include "Particle.h"

/// <summary>
/// 雲パーティクルクラス
/// </summary>
class JumpParticle : public Particle
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	JumpParticle();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~JumpParticle();

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
	const static int PARTICLE_NUMBER = 8;

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
	//	パーティクルごとの速度
	std::vector<DirectX::SimpleMath::Vector3> m_particleVel;

	//  タイマー
	float m_timer;
};
#endif // !JUMP_PARTICLE_DEFINED
