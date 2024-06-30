//--------------------------------------------------------------------------------------
// File: Start.h
//
// スタートクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef START_DEFINED
#define START_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// スタートクラス
/// </summary>
class Start : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Start();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Start();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">座標</param>
	void Initialize();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugRender();
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

public:
	//	開始座標
	static const DirectX::SimpleMath::Vector3 START_POSITION;

private:
	//	モデル
	std::unique_ptr<DirectX::Model> m_model;

	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
};
#endif // !Start_DEFINED