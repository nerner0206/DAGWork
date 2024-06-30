//--------------------------------------------------------------------------------------
// File: FadeCloud.cpp
//
// フェイド用雲画像クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "FadeCloud.h"

#include "MyLib/AudioResources.h"
#include "Game/DataPath.h"

using namespace DirectX;

//	白い画像の拡大率
const float FadeCloud::WHITE_SCALE = 100.0f;
//	移動速度
const float FadeCloud::MOVE_SPEED = 1000.0f;

//	フェイドイン初期座標
const SimpleMath::Vector2 FadeCloud::FADE_IN_START_POSITION = SimpleMath::Vector2(-500.0f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
FadeCloud::FadeCloud()
{

}

/// <summary>
/// デストラクタ
/// </summary>
FadeCloud::~FadeCloud()
{

}

/// <summary>
/// 初期化
/// </summary>
void FadeCloud::Initialize()
{
	//	雲画像の生成
	m_cloud = std::make_unique<UserInterface>();
	m_cloud->Create(
		DataPath::FADE_CLOUD_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One,
		ANCHOR::TOP_LEFT);

	//	白い画像の生成
	m_white= std::make_unique<UserInterface>();
	m_white->Create(
		DataPath::FADE_WHITE_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT) / WHITE_SCALE,
		ANCHOR::TOP_LEFT);
}

/// <summary>
/// フェイドイン初期化
/// </summary>
void FadeCloud::FadeInStart()
{
	//	座標の設定
	m_cloud->SetPosition(FADE_IN_START_POSITION);

	//	透明度の設定
	m_cloud->SetAlpha(1.0f);
	m_white->SetAlpha(1.0f);
}
/// <summary>
/// フェイドイン更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <returns>終了判定</returns>
bool FadeCloud::FadeInUpdate(const float& elapsedTime)
{
	//	座標の取得
	SimpleMath::Vector2 pos = m_cloud->GetPosition();
	//	座標の移動
	pos.x -= elapsedTime * MOVE_SPEED;

	//	透明度の取得
	float alpha = m_cloud->GetAlpha();
	//	透明度の更新
	alpha -= elapsedTime / 2.0f;

	//	ユーザーリソースの取得
	auto ur = UserResources::GetInstance();
	//	透明度で音量設定
	float volume = ur->Lerp(0.0f, AudioResources::MAX_VOLUME, 1.0f - alpha);
	//	音量の設定
	ur->GetAudioEngine()->SetMasterVolume(volume);

	//	透明度の設定
	m_cloud->SetAlpha(alpha);
	m_white->SetAlpha(alpha);

	//	移動の終了判定
	if (pos.x <= -m_cloud->GetTextureSize().x)
	{
		//	座標の設定
		pos.x = UserResources::WINDOW_WIDTH;
		m_cloud->SetPosition(pos);

		//	透明度の設定
		m_cloud->SetAlpha(0.0f);
		m_white->SetAlpha(0.0f);
		//	音量の設定
		ur->GetAudioEngine()->SetMasterVolume(AudioResources::MAX_VOLUME);

		//	フェイドインの終了
		return true;
	}

	//	座標の設定
	m_cloud->SetPosition(pos);
	return false;
}

/// <summary>
/// フェイドアウト初期化
/// </summary>
void FadeCloud::FadeOutStart()
{
	//	座標の設定
	m_cloud->SetPosition(SimpleMath::Vector2(UserResources::WINDOW_WIDTH, 0.0f));

	//	透明度の設定
	m_cloud->SetAlpha(0.0f);
	m_white->SetAlpha(0.0f);
}
/// <summary>
/// フェイドアウト更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <returns>終了判定</returns>
bool FadeCloud::FadeOutUpdate(const float& elapsedTime)
{
	//	座標の取得
	SimpleMath::Vector2 pos = m_cloud->GetPosition();
	//	座標の移動
	pos.x -= elapsedTime * MOVE_SPEED;

	//	透明度の取得
	float alpha = m_cloud->GetAlpha();
	//	透明度の更新
	alpha += elapsedTime / 2.0f;


	//	ユーザーリソースの取得
	auto ur = UserResources::GetInstance();
	//	透明度で音量設定
	float volume =ur->Lerp(AudioResources::MAX_VOLUME, 0.0f, alpha);
	//	音量の設定
	ur->GetAudioEngine()->SetMasterVolume(volume);

	//	透明度の設定
	m_cloud->SetAlpha(alpha);
	m_white->SetAlpha(alpha);

	//	移動の終了判定
	if (pos.x <= FADE_IN_START_POSITION.x)
	{
		//	座標の設定
		pos.x = FADE_IN_START_POSITION.x;
		m_cloud->SetPosition(pos);

		//	透明度の設定
		m_cloud->SetAlpha(1.0f);
		m_white->SetAlpha(1.0f);
		//	音量の設定
		ur->GetAudioEngine()->SetMasterVolume(0.0f);

		//	フェイドアウトの終了
		return true;
	}

	//	座標の設定
	m_cloud->SetPosition(pos);
	return false;
}

/// <summary>
/// 描画
/// </summary>
void FadeCloud::Render()
{
	//	雲画像の描画
	m_cloud->Render();
	//	白い画像の描画
	m_white->Render();
}