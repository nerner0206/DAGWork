//--------------------------------------------------------------------------------------
// File: AudioResources.h
//
// �����\�[�X�N���X�̃w�b�_�[�t�@�C���i�V���O���g�����j
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef AUDIO_RESOURCES_DEFINED
#define AUDIO_RESOURCES_DEFINED

#include <Audio.h>

/// <summary>
/// �����\�[�X�N���X
/// </summary>
class AudioResources
{
public:
	//	���ʂ̍ő�l
	static const float MAX_VOLUME;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AudioResources();
	/// <summary>
	///	�f�X�g���N�^
	/// </summary>
	~AudioResources();

	/// <summary>
	/// �����\�[�X�N���X�̃C���X�^���X�̎擾
	/// </summary>
	/// <returns>�����\�[�X�N���X�̃|�C���^</returns>
	static AudioResources* GetInstance()
	{
		//	�|�C���^������Ă��Ȃ��ꍇ�A�V�����|�C���^���쐬����
		if (s_audioResources.get() == nullptr) 
			s_audioResources.reset(new AudioResources());

		return s_audioResources.get();
	}

	/// <summary>
	/// BGM1�̍Đ�
	/// </summary>
	void PlayBGM1() { m_bgmInstance->Play(true); }
	/// <summary>
	/// BGM1�̒�~
	/// </summary>
	void StopBGM1() { m_bgmInstance->Stop(); }

	/// <summary>
	/// BGM2�̍Đ�
	/// </summary>
	void PlayBGM2() { m_playBgmInstance->Play(true); }
	/// <summary>
	/// BGM2�̒�~
	/// </summary>
	void StopBGM2() { m_playBgmInstance->Stop(); }

	/// <summary>
	/// ����SE�̍Đ�
	/// </summary>
	void PlayDecideSE() { m_decideSE->Play(); }
	/// <summary>
	/// �I��SE�̍Đ�
	/// </summary>
	void PlaySelectSE() { m_selectSE->Play(); }
	/// <summary>
	/// �ݒ�SE�̍Đ�
	/// </summary>
	void PlaySystemSE() { m_systemSE->Play(); }

	/// <summary>
	/// �΂�SE�̍Đ�
	/// </summary>
	void PlaySpringSE() { m_springSE->Play(); }
	/// <summary>
	/// �W�����vSE�̍Đ�
	/// </summary>
	void PlayJumpSE() { m_jumpSE->Play(); }
	/// <summary>
	/// ����SE�̍Đ�
	/// </summary>
	void PlayExplosionSE() { m_explosionSE->Play(); }
	/// <summary>
	/// �j��SE�̍Đ�
	/// </summary>
	void PlayBalloonSE() { m_balloonSE->Play(); }
	/// <summary>
	/// ��SE�̍Đ�
	/// </summary>
	void PlayWindSE() { m_windSE->Play(); }

	/// <summary>
	/// �N���b�J�[�@SE�̍Đ�
	/// </summary>
	void PlayCracker01SE() { m_cracker01SE->Play(); }
	/// <summary>
	/// �N���b�J�[�ASE�̍Đ�
	/// </summary>
	void PlayCracker02SE() { m_cracker02SE->Play(); }

	/// <summary>
	/// �N���ASE�̍Đ�
	/// </summary>
	void PlayClearSE() { m_clearSE->Play(); }
	/// <summary>
	/// ���SSE�̍Đ�
	/// </summary>
	void PlayDeadSE() { m_deadSE->Play(); }

private:
	//	�����\�[�X�N���X�̃|�C���^
	static std::unique_ptr<AudioResources> s_audioResources;

	//	BGM1�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_bgm;
	//	BGM1�C���X�^���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgmInstance;

	//	BGM2�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_playBgm;
	//	BGM2�C���X�^���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffectInstance> m_playBgmInstance;

	//	����SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_decideSE;
	//	���SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_selectSE;
	//	�ݒ�SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_systemSE;

	//	�΂�SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_springSE;
	//	�W�����vSE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_jumpSE;
	//	����SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_explosionSE;
	//	�j��SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_balloonSE;
	//	��SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_windSE;

	//	�N���b�J�[�@SE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_cracker01SE;
	//	�N���b�J�[�ASE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_cracker02SE;

	//	�N���ASE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_clearSE;
	//	���SSE�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::SoundEffect> m_deadSE;
};
#endif // !AUDIO_RESOURCES_DEFINED