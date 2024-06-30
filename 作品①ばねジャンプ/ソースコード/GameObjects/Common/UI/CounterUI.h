//--------------------------------------------------------------------------------------
// File: CounterUI.h
//
// カウンターUIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef COUNTER_UI_DEFINED
#define COUNTER_UI_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// スペースUIクラス
/// </summary>
class CounterUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CounterUI();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CounterUI();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// 描画
	/// </summary>
	void Render(const int& count);

private:
	//	二桁目の座標のオフセット
	static const DirectX::SimpleMath::Vector2 FIRST_OFFSET;
	//	二桁目の座標のオフセット
	static const DirectX::SimpleMath::Vector2 SECOND_OFFSET;
	//	三桁目の座標のオフセット
	static const DirectX::SimpleMath::Vector2 THIRD_OFFSET;
	//	四桁目の座標のオフセット
	static const DirectX::SimpleMath::Vector2 FOURTH_OFFSET;

private:
	//	中心座標
	DirectX::SimpleMath::Vector2 m_centerPos;

	//	一桁目の座標
	DirectX::SimpleMath::Vector2 m_firstPos;
	//	二桁目の座標
	DirectX::SimpleMath::Vector2 m_secondPos;
	//	三桁目の座標
	DirectX::SimpleMath::Vector2 m_thirdPos;
	//	四桁目の座標
	DirectX::SimpleMath::Vector2 m_fourthPos;

	//	数字UIのユニークポインタ配列
	std::vector<std::unique_ptr<UserInterface>> m_numbersUI;

	//	中心アイコンUIのユニークポインタ配列
	std::unique_ptr<UserInterface> m_centerUI;
};
#endif // !COUNTER_UI_DEFINED