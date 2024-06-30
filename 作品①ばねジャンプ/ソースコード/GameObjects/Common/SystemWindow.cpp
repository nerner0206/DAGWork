//--------------------------------------------------------------------------------------
// File: SystemWindow.cpp
//
// 設定画面クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemWindow.h"

#include "GameObjects/Common/UI/System/SystemMouseUI.h"
#include "GameObjects/Common/UI/System/SystemSelectUI.h"
#include "GameObjects/Common/UI/System/SystemTitleUI.h"
#include "GameObjects/Common/UI/System/SystemExitUI.h"

#include "Scenes/PlayScene.h"
#include "MyLib/SceneManager.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SystemWindow::SystemWindow() :
	m_isSystemOpen(false),
	m_selectNum(0),
	m_selectMaxNum(DataPath::SYSTEM_SELECT_NUMBER)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SystemWindow::~SystemWindow()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void SystemWindow::Initialize(const int& mouseNumber)
{
	//	選択肢の生成
	CreateUI(mouseNumber);

	//	選択フレームの生成
	m_itemFrame = std::make_unique<UserInterface>();
	m_itemFrame->Create(
		DataPath::SYSTEM_FRAME_IMAGE_PATH,
		m_items[0]->GetPos(),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//	背景の生成
	m_back = std::make_unique<UserInterface>();
	m_back->Create(
		DataPath::SYSTEM_BACK_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One,
		ANCHOR::TOP_LEFT);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
void SystemWindow::Update(IScene* scene)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	ESCキーが押されたら設定画面の終了
	if (kbTracker->pressed.Escape)
	{
		OffWindow(scene);
		return;
	}

	//	上下移動
	if (kbTracker->pressed.Up && m_selectNum > 0)
	{
		//	設定音の再生
		AudioResources::GetInstance()->PlaySelectSE();
		//	選択番号の更新
		m_selectNum--;
	}
	else if (kbTracker->pressed.Down && m_selectNum < m_selectMaxNum - 1)
	{
		//	設定音の再生
		AudioResources::GetInstance()->PlaySelectSE();
		//	選択番号の更新
		m_selectNum++;
	}

	//	フレームの移動
	MoveFrame();

	//	各選択肢の更新
	m_items[m_selectNum]->Update(scene, this);
}

/// <summary>
/// 描画
/// </summary>
void SystemWindow::Render()
{
	//	背景の描画
	m_back->Render();

	//	各選択肢の描画
	for (auto& item : m_items)
	{
		item->Render();
	}

	//	選択フレームの描画
	m_itemFrame->Render();
}

/// <summary>
/// 終了
/// </summary>
void SystemWindow::Finalize() 
{

}

/// <summary>
/// 設定画面の開始
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
void SystemWindow::OnWindow(IScene* scene)
{
	//	設定音の再生
	AudioResources::GetInstance()->PlaySystemSE();

	//	開く状態へ
	m_isSystemOpen = true;

	//	選択肢番号の初期化
	m_selectNum = 0;
}

/// <summary>
/// 設定画面の終了
/// </summary>
/// <param name="scene">シーンクラスのポインタ</param>
void SystemWindow::OffWindow(IScene* scene)
{
	//	設定音の再生
	AudioResources::GetInstance()->PlaySystemSE();

	//	閉じる状態へ
	m_isSystemOpen = false;

	//	マウス感度の番号の取得
	SystemMouseUI* mouseUI = dynamic_cast<SystemMouseUI*>(m_items[0].get());
	int m_num = mouseUI->GetMouseNumber();

	//	システム設定の保存
	scene->GetSceneManager()->SaveSystem(m_num);

	//	プレイシーンの場合、即座に感度を設定する
	if (scene->GetSceneKind() != IScene::SceneKind::PlayScene) return;

	//	プレイシーンへキャスト
	PlayScene* play = dynamic_cast<PlayScene*>(scene);
	//	感度の設定
	play->SetMouseSpeed(m_num);
}

/// <summary>
/// 選択フレームを動かす
/// </summary>
void SystemWindow::MoveFrame()
{
	SimpleMath::Vector2 pos = m_items[m_selectNum]->GetPos();
	m_itemFrame->SetPosition(pos);
}

/// <summary>
/// 各UIの生成
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void SystemWindow::CreateUI(const int& mouseNumber)
{
	//	基準y座標
	float y = UserResources::WINDOW_HEIGHT / 2 - ITEM_DISTANCE * (DataPath::SYSTEM_SELECT_NUMBER / 2);
	//	座標
	SimpleMath::Vector2 pos = SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, y + ITEM_DISTANCE);

	//	各選択肢の生成
	m_items.push_back(std::make_unique<SystemMouseUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[0], pos, mouseNumber));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemSelectUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[1], pos));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemTitleUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[2], pos));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemExitUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[3], pos));
	
	//	初期化
	for (auto& item : m_items)
	{
		item->Initialize();
	}
}