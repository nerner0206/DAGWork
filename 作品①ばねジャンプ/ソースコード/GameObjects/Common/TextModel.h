//--------------------------------------------------------------------------------------
// File: TextModel.h
//
// 文字モデルクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef TEXT_MODEL_DEFINED
#define TEXT_MODEL_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// 文字モデルクラス
/// </summary>
class TextModel : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TextModel();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextModel();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="filePath">モデルのファイルパス</param>
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
#endif // !TEXT_MODEL_DEFINED