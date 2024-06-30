//--------------------------------------------------------------------------------------
// File: SystemExitUI.h
//
// 終了設定UIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_EXIT_UI_DEFINED
#define SYSTEM_EXIT_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

/// <summary>
/// 終了設定UIクラス
/// </summary>
class SystemExitUI : public SystemUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemExitUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SystemExitUI();

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
#endif // !SYSTEM_EXIT_UI_DEFINED