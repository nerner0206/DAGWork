//--------------------------------------------------------------------------------------
// File: Balloon.h
//
// 風船クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BALLOON_DEFINED
#define BALLOON_DEFINED

#include "GameObjects/PlayScene/StageObjects/IStageObject.h"

/// <summary>
/// 風船クラス
/// </summary>
class Balloon : public IStageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	Balloon(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Balloon();

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
	/// 割れる
	/// </summary>
	void Break();

private:
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS;
};
#endif // !Balloon_DEFINED