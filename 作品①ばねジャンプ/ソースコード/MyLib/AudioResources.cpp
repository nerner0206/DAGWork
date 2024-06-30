//--------------------------------------------------------------------------------------
// File: AudioResources.cpp
//
// �����\�[�X�N���X�̃w�b�_�[�t�@�C���i�V���O���g�����j
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "AudioResources.h"

#include "MyLib/UserResources.h"
#include "Game/DataPath.h"

//	���ʂ̍ő�l
const float AudioResources::MAX_VOLUME = 0.5f;

std::unique_ptr<AudioResources> AudioResources::s_audioResources = nullptr;

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
AudioResources::AudioResources()
{
	//	���[�U�[���\�[�X�̎擾
	UserResources* ur = UserResources::GetInstance();

	//	���ʐݒ�
	ur->GetAudioEngine()->SetMasterVolume(MAX_VOLUME);

	//	BGM1�̐���
	m_bgm = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::BGM_PATH);
	m_bgmInstance = m_bgm->CreateInstance();

	//	BGM2�̐���
	m_playBgm = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::PLAY_BGM_PATH);
	m_playBgmInstance = m_playBgm->CreateInstance();

	//	����SE�̐���
	m_decideSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::DECIDE_SE_PATH);
	//	�I��SE�̐���
	m_selectSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::ARROW_SE_PATH);
	//	�ݒ�SE�̐���
	m_systemSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::SYSTEM_SE_PATH);

	//	�΂�SE�̐���
	m_springSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::SPRING_SE_PATH);
	//	�W�����vSE�̐���
	m_jumpSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::JUMP_SE_PATH);
	//	����SE�̐���
	m_explosionSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::EXPLOSION_SE_PATH);
	//	�j��SE�̐���
	m_balloonSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::BALLOON_SE_PATH);
	//	��SE�̐���
	m_windSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::WIND_SE_PATH);

	//	�N���b�J�[�@SE�̐���
	m_cracker01SE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CRACKER01_SE_PATH);
	//	�N���b�J�[�ASE�̐���
	m_cracker02SE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CRACKER02_SE_PATH);

	//	�N���ASE�̐���
	m_clearSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::CREAR_SE_PATH);
	//	���SSE�̐���
	m_deadSE = std::make_unique<SoundEffect>(ur->GetAudioEngine(), DataPath::DEAD_SE_PATH);
}

/// <summary>
///	�f�X�g���N�^
/// </summary>
AudioResources::~AudioResources()
{

}