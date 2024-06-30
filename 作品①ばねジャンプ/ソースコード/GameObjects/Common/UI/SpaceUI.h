//--------------------------------------------------------------------------------------
// File: SpaceUI.h
//
// スペースUIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPACE_UI_DEFINED
#define SPACE_UI_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// スペースUIクラス
/// </summary>
class SpaceUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpaceUI();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpaceUI();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// 描画
	/// </summary>
	void Render();

private:
	//	スペース１画像
	std::unique_ptr<UserInterface> m_Space_01;
	//	スペース２画像
	std::unique_ptr<UserInterface> m_Space_02;

	//	カウント
	int count;
};
#endif // !SPACE_UI_DEFINED