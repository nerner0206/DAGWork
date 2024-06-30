//--------------------------------------------------------------------------------------
// File: SystemUI.h
//
// 設定UIクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_UI_DEFINED
#define SYSTEM_UI_DEFINED

#include "MyLib/AudioResources.h"
#include "MyLib/UserInterface.h"
#include "Game/DataPath.h"

class SystemWindow;
class IScene;

/// <summary>
/// スペースUIクラス
/// </summary>
class SystemUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos)
	{
		//	音リソースクラスの取得
		m_ar = AudioResources::GetInstance();

		//	画像の生成
		m_image = std::make_unique<UserInterface>();
		m_image->Create(
			fileName,
			pos,
			DirectX::SimpleMath::Vector2::One,
			ANCHOR::MIDDLE_CENTER);
	}

	/// <summary>
	/// 音リソースクラスの取得
	/// </summary>
	/// <returns>音リソースクラスのポインタ</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const DirectX::SimpleMath::Vector2 GetPos() { return m_image->GetPosition(); }

	/// <summary>
	/// UIの取得
	/// </summary>
	/// <returns>UIのポインタ</returns>
	UserInterface* GetImage() { return m_image.get(); }

public:
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~SystemUI() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="scene">シーン基底クラスのポインタ</param>
	/// <param name="window">設定画面クラスのポインタ</param>
	virtual void Update(IScene* scene, SystemWindow* window) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Render() = 0;

private:
	//	音リソースクラスのポインタ
	AudioResources* m_ar;
	//	UIのユニークポインタ
	std::unique_ptr<UserInterface> m_image;
};
#endif // !System_UI_DEFINED