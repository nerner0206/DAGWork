//--------------------------------------------------------------------------------------
// File: SystemTitleUI.h
//
// タイトル設定UIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_TITLE_UI_DEFINED
#define SYSTEM_TITLE_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

/// <summary>
/// タイトル設定UIクラス
/// </summary>
class SystemTitleUI : public SystemUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemTitleUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SystemTitleUI();

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
};
#endif // !SYSTEM_TITLE_UI_DEFINED