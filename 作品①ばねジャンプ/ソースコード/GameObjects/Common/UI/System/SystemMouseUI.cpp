//--------------------------------------------------------------------------------------
// File: SystemMouseUI.h
//
// マウス感度設定UIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemMouseUI.h"

#include "MyLib/IScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

//	番号の基準座標
const SimpleMath::Vector2 SystemMouseUI::NUM_POSITION = SimpleMath::Vector2(580, 240);

/// <summary>
/// コンストラクタ
/// </summary>
SystemMouseUI::SystemMouseUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos, const int& num) :
	SystemUI(fileName, pos),
	m_moveNum(num)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SystemMouseUI::~SystemMouseUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void SystemMouseUI::Initialize()
{
	//	番号UIの生成
	for (int i = 0; i < DataPath::SYSTEM_MOUSE_NUMBER; i++)
	{
		//	UIの生成
		std::unique_ptr<UserInterface> numUI = std::make_unique<UserInterface>();
		numUI->Create(
			DataPath::NUMBER_IMAGE_PATHs[i + 1],
			NUM_POSITION + SimpleMath::Vector2(i * NUM_DISTANCE, 0),
			SimpleMath::Vector2::One * 0.4f,
			ANCHOR::MIDDLE_CENTER);

		//	配列へ追加
		m_numUIs.push_back(std::move(numUI));
	}

	//	選択肢UIの生成
	m_frame = std::make_unique<UserInterface>();
	m_frame->Create(
		DataPath::SYSTEM_MOUSE_FRAME_IMAGE_PATH,
		m_numUIs[m_moveNum]->GetPosition(),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
/// <param name="window">設定画面クラスのポインタ</param>
void SystemMouseUI::Update(IScene* scene, SystemWindow* window)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	左右移動
	if (kbTracker->pressed.Left && m_moveNum > 0)
	{
		//	選択音の再生
		GetAudioResources()->PlaySelectSE();
		//	感度番号の変更
		m_moveNum--;
	}	
	else if (kbTracker->pressed.Right && m_moveNum < DataPath::SYSTEM_MOUSE_NUMBER - 1)
	{
		//	選択音の再生
		GetAudioResources()->PlaySelectSE();
		//	感度番号の変更
		m_moveNum++;
	}

	//	選択肢の座標の更新
	m_frame->SetPosition(m_numUIs[m_moveNum]->GetPosition());
}

/// <summary>
/// 描画
/// </summary>
void SystemMouseUI::Render()
{
	//	UIの描画
	GetImage()->Render();

	//	番号UIの描画
	for (auto& numUI : m_numUIs)
	{
		numUI->Render();
	}

	//	選択フレームの描画
	m_frame->Render();
}