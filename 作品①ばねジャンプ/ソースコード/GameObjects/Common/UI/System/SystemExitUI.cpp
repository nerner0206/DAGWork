//--------------------------------------------------------------------------------------
// File: SystemExitUI.h
//
// 終了設定UIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemExitUI.h"

#include "MyLib/IScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SystemExitUI::SystemExitUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SystemExitUI::~SystemExitUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void SystemExitUI::Initialize()
{
	
}

/// <summary>
/// 更新
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
/// <param name="window">設定画面クラスのポインタ</param>
void SystemExitUI::Update(IScene* scene, SystemWindow* window)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	
	//	エンターキーで終了
	if (kbTracker->pressed.Space)
	{
		//	決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	ゲームの終了
		PostQuitMessage(0);
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
void SystemExitUI::Render()
{
	//	UIの描画
	GetImage()->Render();
}