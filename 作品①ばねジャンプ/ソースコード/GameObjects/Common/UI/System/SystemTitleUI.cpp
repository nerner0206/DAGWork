//--------------------------------------------------------------------------------------
// File: SystemTitleUI.h
//
// タイトル設定UIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemTitleUI.h"

#include "Scenes/TitleScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SystemTitleUI::SystemTitleUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SystemTitleUI::~SystemTitleUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void SystemTitleUI::Initialize()
{
	
}

/// <summary>
/// 更新
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
/// <param name="window">設定画面クラスのポインタ</param>
void SystemTitleUI::Update(IScene* scene, SystemWindow* window)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	エンターキーでタイトルシーンへ
	if (kbTracker->pressed.Space)
	{
		//	決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	タイトルシーンへ
		scene->GetSceneManager()->SetNextScene(new TitleScene());
		//	設定画面を閉じる
		window->OffWindow(scene);
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
void SystemTitleUI::Render()
{
	//	UIの描画
	GetImage()->Render();
}