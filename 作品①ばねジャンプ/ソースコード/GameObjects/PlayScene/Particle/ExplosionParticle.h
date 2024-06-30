//--------------------------------------------------------------------------------------
// File: ExplosionParticle.h
//
// 爆発パーティクルクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef EXPLOSION_PARTICLE_DEFINED
#define EXPLOSION_PARTICLE_DEFINED

#include "Particle.h"

/// <summary>
/// 爆発パーティクルクラス
/// </summary>
class ExplosionParticle : public Particle
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ExplosionParticle();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ExplosionParticle();

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
	static const DirectX::VertexPositionTexture VERTICES[4];
	//	拡大率
	static const float MAX_SCALE;

private:
	// 入力レイアウトのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル のコムポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textures[DataPath::EXPLOSION_PARTICLE_IMAGE_NUM];
	// エフェクト のユニークポインタ
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// プリミティブバッチ のユニークポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//  タイマー
	float m_timer;
	//	画像番号
	int m_texNum;
};
#endif // !JUMP_PARTICLE_DEFINED
