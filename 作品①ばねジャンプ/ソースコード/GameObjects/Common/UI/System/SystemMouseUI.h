//--------------------------------------------------------------------------------------
// File: SystemMouseUI.h
//
// マウス感度設定UIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_MOUSE_UI_DEFINED
#define SYSTEM_MOUSE_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

#include <vector>

/// <summary>
/// マウス感度設定UIクラス
/// </summary>
class SystemMouseUI : public SystemUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemMouseUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos, const int& num);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SystemMouseUI();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="scene">シーン基底クラスのポインタ</param>
	/// <param name="window">設定画面クラスのポインタ</param>
	void Update(IScene* scene, SystemWindow* window) override;
	/// <summary>
	/// 描画
	/// </summary>
	void Render() override;

	/// <summary>
	/// マウス感度番号の設定
	/// </summary>
	/// <param name="num">マウス感度番号</param>
	void SetMouseNumber(const int& num) { m_moveNum = num; }
	/// <summary>
	/// マウス感度番号の取得
	/// </summary>
	/// <returns>マウス感度番号</returns>
	const int GetMouseNumber() { return m_moveNum; }

private:
	//	番号の間隔
	static const int NUM_DISTANCE = 30;

	//	番号の基準座標
	static const DirectX::SimpleMath::Vector2 NUM_POSITION;

private:
	//	選択番号
	int m_moveNum;

	//	番号UIのユニークポインタ配列
	std::vector<std::unique_ptr<UserInterface>> m_numUIs;
	//	選択フレームUIのユニークポインタ
	std::unique_ptr<UserInterface> m_frame;
};
#endif // !SYSTEM_MOUSE_UI_DEFINED