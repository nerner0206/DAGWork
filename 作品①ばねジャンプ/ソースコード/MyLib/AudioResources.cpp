//--------------------------------------------------------------------------------------
// File: AudioResources.cpp
//
// 音リソースクラスのヘッダーファイル（シングルトン化）
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "AudioResources.h"

#include "MyLib/UserResources.h"
#include "Game/DataPath.h"

//	音量の最大値
const float AudioResources::MAX_VOLUME = 0.5f;

std::unique_ptr<AudioResources> AudioResources::s_audioResources = nullptr;

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
AudioResources::AudioResources()
{
	//	ユーザーリソースの取得
	UserResources* ur = UserResources::GetInstance();

	//	音量設定
	ur->GetAudioEngine()->SetMasterVolume(MAX_VOLUME);

	//	BGM1の生成
	m_bgm = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::BGM_PATH);
	m_bgmInstance = m_bgm->CreateInstance();

	//	BGM2の生成
	m_playBgm = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::PLAY_BGM_PATH);
	m_playBgmInstance = m_playBgm->CreateInstance();

	//	決定SEの生成
	m_decideSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::DECIDE_SE_PATH);
	//	選択SEの生成
	m_selectSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::ARROW_SE_PATH);
	//	設定SEの生成
	m_systemSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::SYSTEM_SE_PATH);

	//	ばねSEの生成
	m_springSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::SPRING_SE_PATH);
	//	ジャンプSEの生成
	m_jumpSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::JUMP_SE_PATH);
	//	爆発SEの生成
	m_explosionSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::EXPLOSION_SE_PATH);
	//	破裂SEの生成
	m_balloonSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::BALLOON_SE_PATH);
	//	風SEの生成
	m_windSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::WIND_SE_PATH);

	//	クラッカー①SEの生成
	m_cracker01SE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CRACKER01_SE_PATH);
	//	クラッカー②SEの生成
	m_cracker02SE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CRACKER02_SE_PATH);

	//	クリアSEの生成
	m_clearSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CREAR_SE_PATH);
	//	死亡SEの生成
	m_deadSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::DEAD_SE_PATH);
}

/// <summary>
///	デストラクタ
/// </summary>
AudioResources::~AudioResources()
{

}