//--------------------------------------------------------------------------------------
// File: Cloud.h
//
// 雲クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef CLOUD_DEFINED
#define CLOUD_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// 雲クラス
/// </summary>
class Cloud : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Cloud();
	/// <summary>
	///	デストラクタ
	/// </summary>
	~Cloud();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="filePath">雲モデルのファイルパス</param>
	void Initialize(const wchar_t* filePath);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

private:
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//	モデルクラスのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;
};
#endif // !CLOUD_DEFINED