//--------------------------------------------------------------------------------------
// File: SystemSelectUI.h
//
// セレクト設定UIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemSelectUI.h"

#include "Scenes/SelectScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SystemSelectUI::SystemSelectUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SystemSelectUI::~SystemSelectUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void SystemSelectUI::Initialize()
{
	
}

/// <summary>
/// 更新
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
/// <param name="window">設定画面クラスのポインタ</param>
void SystemSelectUI::Update(IScene* scene, SystemWindow* window)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	エンターキーでセレクトシーンへ
	if (kbTracker->pressed.Space)
	{
		//	決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	セレクトシーンへ
		scene->GetSceneManager()->SetNextScene(new SelectScene());
		//	設定画面を閉じる
		window->OffWindow(scene);
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
void SystemSelectUI::Render()
{
	//	UIの描画
	GetImage()->Render();
}