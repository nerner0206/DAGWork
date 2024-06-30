//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// �l�X�ȏꏊ�Ŏg�p���郆�[�U�[���\�[�X�N���X�̃w�b�_�[�t�@�C���i�V���O���g�����j
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef USER_RESOURCES_DEFINED
#define USER_RESOURCES_DEFINED

#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

#include "Common/ShadowMap.h"

#include <Keyboard.h>
#include <Mouse.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Effects.h>
#include <Audio.h>

/// <summary>
/// ���[�U�[���\�[�X�N���X
/// </summary>
class UserResources
{
public:
	//	�E�B���h�E�̕�
	static const int WINDOW_WIDTH = 1280;
	//	�E�B���h�E�̍���
	static const int WINDOW_HEIGHT = 720;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UserResources();
	/// <summary>
	///	�f�X�g���N�^
	/// </summary>
	~UserResources();

	/// <summary>
	/// ���[�U�[���\�[�X�N���X�̃C���X�^���X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	static UserResources* GetInstance()
	{
		//	�|�C���^������Ă��Ȃ��ꍇ�A�V�����|�C���^���쐬����
		if (s_userResources.get() == nullptr) 
			s_userResources.reset(new UserResources());

		return s_userResources.get();
	}

	/// <summary>
	/// �X�e�b�v�^�C�}�[�N���X�̐ݒ�
	/// </summary>
	/// <param name="timer">�X�e�b�v�^�C�}�[�N���X�̃|�C���^</param>
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }
	/// <summary>
	/// �X�e�b�v�^�C�}�[�N���X�̎擾
	/// </summary>
	/// <returns>�X�e�b�v�^�C�}�[�N���X�̃|�C���^</returns>
	DX::StepTimer* GetStepTimer() { return m_timer; }

	/// <summary>
	/// �f�o�C�X���\�[�X�N���X�̐ݒ�
	/// </summary>
	/// <param name="deviceResources">�f�o�C�X���\�[�X�N���X�̃|�C���^</param>
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }
	/// <summary>
	/// �f�o�C�X���\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>�f�o�C�X���\�[�X�N���X�̃|�C���^</returns>
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }

	/// <summary>
	/// �L�[�{�[�h�X�e�[�g�g���b�J�[�N���X�̐ݒ�
	/// </summary>
	/// <param name="tracker">�L�[�{�[�h�X�e�[�g�g���b�J�[�N���X�̃|�C���^</param>
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_keyboardTracker = tracker; }
	/// <summary>
	/// �L�[�{�[�h�X�e�[�g�g���b�J�[�N���X�̎擾
	/// </summary>
	/// <returns>�L�[�{�[�h�X�e�[�g�g���b�J�[�N���X�̃|�C���^</returns>
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardTracker; }

	/// <summary>
	/// �}�E�X�X�e�[�g�g���b�J�[�N���X�̐ݒ�
	/// </summary>
	/// <param name="tracker">�}�E�X�X�e�[�g�g���b�J�[�N���X�̃|�C���^</param>
	void SetMouseStateTracker(DirectX::Mouse::ButtonStateTracker* tracker) { m_mouseTracker = tracker; }
	/// <summary>
	/// �}�E�X�X�e�[�g�g���b�J�[�N���X�̎擾
	/// </summary>
	/// <returns>�}�E�X�X�e�[�g�g���b�J�[�N���X�̃|�C���^</returns>
	DirectX::Mouse::ButtonStateTracker* GetMouseStateTracker() { return m_mouseTracker; }

	/// <summary>
	/// ���ʃX�e�[�g�N���X�̐ݒ�
	/// </summary>
	/// <param name="states">���ʃX�e�[�g�N���X�̃|�C���^</param>
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }
	/// <summary>
	/// ���ʃX�e�[�g�N���X�̎擾
	/// </summary>
	/// <returns>���ʃX�e�[�g�N���X�̃|�C���^</returns>
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	/// <summary>
	/// �I�[�f�B�I�G���W���̐ݒ�
	/// </summary>
	/// <param name="audioEngine">�I�[�f�B�I�G���W���̃|�C���^</param>
	void SetAudioEngine(DirectX::AudioEngine* audioEngine) { m_audioEngine = audioEngine; }
	/// <summary>
	/// �I�[�f�B�I�G���W���̎擾
	/// </summary>
	/// <returns>�I�[�f�B�I�G���W���̃|�C���^</returns>
	DirectX::AudioEngine* GetAudioEngine() { return m_audioEngine; }

	/// <summary>
	/// �V���h�E�}�b�v�N���X�̐ݒ�
	/// </summary>
	/// <param name="shadowMap">�V���h�E�}�b�v�N���X�̃|�C���^</param>
	void SetShadowMap(ShadowMap* shadowMap) { m_shadowMap = shadowMap; }
	/// <summary>
	/// �V���h�E�}�b�v�N���X�̎擾
	/// </summary>
	/// <returns>�V���h�E�}�b�v�N���X�̃|�C���^</returns>
	ShadowMap* GetShadowMap() { return m_shadowMap; }

	/// <summary>
	/// ���S���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetCenterPos(const DirectX::SimpleMath::Vector2& pos) { m_centerPos = pos; }

	/// <summary>
	/// ���S���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	const DirectX::SimpleMath::Vector2 GetCenterPos() { return m_centerPos; }

	/// <summary>
	/// ���[�v�֐�
	/// </summary>
	/// <param name="start">�J�n�l</param>
	/// <param name="end">�I���l</param>
	/// <param name="t">����</param>
	/// <returns>��Ԓl</returns>
	float Lerp(float start, float end, float t) { return (1 - t) * start + t * end; }

private:
	//	���[�U�[���\�[�X�N���X�̃|�C���^
	static std::unique_ptr<UserResources> s_userResources;

	// �X�e�b�v�^�C�}�[�N���X�̃|�C���^
	DX::StepTimer* m_timer;
	// �f�o�C�X���\�[�X�N���X�̃|�C���^
	DX::DeviceResources* m_deviceResources;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�N���X�̃|�C���^
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;
	// �}�E�X�X�e�[�g�g���b�J�[�N���X�̃|�C���^
	DirectX::Mouse::ButtonStateTracker* m_mouseTracker;
	// ���ʃX�e�[�g�N���X�̃|�C���^
	DirectX::CommonStates* m_states;
	//	�V���h�E�}�b�v�N���X�̃|�C���^
	ShadowMap* m_shadowMap;
	//	�I�[�f�B�I�G���W���̃|�C���^
	DirectX::AudioEngine* m_audioEngine;

	//	��ʂ̒��S���W
	DirectX::SimpleMath::Vector2 m_centerPos;
};
#endif // !USER_RESOURCES_DEFINED