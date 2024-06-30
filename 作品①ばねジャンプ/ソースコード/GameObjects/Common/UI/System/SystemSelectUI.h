//--------------------------------------------------------------------------------------
// File: SystemSelectUI.h
//
// セレクト設定UIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_SELECT_UI_DEFINED
#define SYSTEM_SELECT_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

/// <summary>
/// セレクト設定UIクラス
/// </summary>
class SystemSelectUI : public SystemUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemSelectUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SystemSelectUI();

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
#endif // !SYSTEM_SELECT_UI_DEFINED