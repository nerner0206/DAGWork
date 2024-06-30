//--------------------------------------------------------------------------------------
// File: PlayerHead.h
//
// プレイヤー頭クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_HEAD_DEFINED
#define PLAYER_HEAD_DEFINED

#include "Player.h"

/// <summary>
/// プレイヤー頭クラス
/// </summary>
class PlayerHead : public PlayerComponent
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="p">プレイヤークラスのポインタ</param>
	/// <param name="parent">親のポインタ</param>
	PlayerHead(Player* p, PlayerComponent* parent);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHead();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	/// <param name="stageObjects">ステージ管理クラスのポインタ</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		StageManager* stageManager) override;
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
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	void Reset(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;

	/// <summary>
	/// データの保存
	/// </summary>
	void SaveData() override;

	/// <summary>
	/// 衝突の取得
	/// </summary>
	/// <returns>衝突判定</returns>
	bool GetHit() const { return m_hit; }
	/// <summary>
	/// 衝突の設定
	/// </summary>
	/// <param name="hit">衝突判定</param>
	void SetHit(const bool& hit) { m_hit = hit; }

public:
	//	頭のデフォルトサイズ
	const static DirectX::SimpleMath::Vector3 PLAYER_HEAD_SIZE;

private:
	//	モデルクラスのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;
	//	衝突判定
	bool m_hit;
};
#endif // !PLAYER_HEAD_DEFINED