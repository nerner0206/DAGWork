//--------------------------------------------------------------------------------------
// File: FadeCloud.cpp
//
// �t�F�C�h�p�_�摜�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "FadeCloud.h"

#include "MyLib/AudioResources.h"
#include "Game/DataPath.h"

using namespace DirectX;

//	�����摜�̊g�嗦
const float FadeCloud::WHITE_SCALE = 100.0f;
//	�ړ����x
const float FadeCloud::MOVE_SPEED = 1000.0f;

//	�t�F�C�h�C���������W
const SimpleMath::Vector2 FadeCloud::FADE_IN_START_POSITION = SimpleMath::Vector2(-500.0f, 0.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeCloud::FadeCloud()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FadeCloud::~FadeCloud()
{

}

/// <summary>
/// ������
/// </summary>
void FadeCloud::Initialize()
{
	//	�_�摜�̐���
	m_cloud = std::make_unique<UserInterface>();
	m_cloud->Create(
		DataPath::FADE_CLOUD_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One,
		ANCHOR::TOP_LEFT);

	//	�����摜�̐���
	m_white= std::make_unique<UserInterface>();
	m_white->Create(
		DataPath::FADE_WHITE_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT) / WHITE_SCALE,
		ANCHOR::TOP_LEFT);
}

/// <summary>
/// �t�F�C�h�C��������
/// </summary>
void FadeCloud::FadeInStart()
{
	//	���W�̐ݒ�
	m_cloud->SetPosition(FADE_IN_START_POSITION);

	//	�����x�̐ݒ�
	m_cloud->SetAlpha(1.0f);
	m_white->SetAlpha(1.0f);
}
/// <summary>
/// �t�F�C�h�C���X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <returns>�I������</returns>
bool FadeCloud::FadeInUpdate(const float& elapsedTime)
{
	//	���W�̎擾
	SimpleMath::Vector2 pos = m_cloud->GetPosition();
	//	���W�̈ړ�
	pos.x -= elapsedTime * MOVE_SPEED;

	//	�����x�̎擾
	float alpha = m_cloud->GetAlpha();
	//	�����x�̍X�V
	alpha -= elapsedTime / 2.0f;

	//	���[�U�[���\�[�X�̎擾
	auto ur = UserResources::GetInstance();
	//	�����x�ŉ��ʐݒ�
	float volume = ur->Lerp(0.0f, AudioResources::MAX_VOLUME, 1.0f - alpha);
	//	���ʂ̐ݒ�
	ur->GetAudioEngine()->SetMasterVolume(volume);

	//	�����x�̐ݒ�
	m_cloud->SetAlpha(alpha);
	m_white->SetAlpha(alpha);

	//	�ړ��̏I������
	if (pos.x <= -m_cloud->GetTextureSize().x)
	{
		//	���W�̐ݒ�
		pos.x = UserResources::WINDOW_WIDTH;
		m_cloud->SetPosition(pos);

		//	�����x�̐ݒ�
		m_cloud->SetAlpha(0.0f);
		m_white->SetAlpha(0.0f);
		//	���ʂ̐ݒ�
		ur->GetAudioEngine()->SetMasterVolume(AudioResources::MAX_VOLUME);

		//	�t�F�C�h�C���̏I��
		return true;
	}

	//	���W�̐ݒ�
	m_cloud->SetPosition(pos);
	return false;
}

/// <summary>
/// �t�F�C�h�A�E�g������
/// </summary>
void FadeCloud::FadeOutStart()
{
	//	���W�̐ݒ�
	m_cloud->SetPosition(SimpleMath::Vector2(UserResources::WINDOW_WIDTH, 0.0f));

	//	�����x�̐ݒ�
	m_cloud->SetAlpha(0.0f);
	m_white->SetAlpha(0.0f);
}
/// <summary>
/// �t�F�C�h�A�E�g�X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <returns>�I������</returns>
bool FadeCloud::FadeOutUpdate(const float& elapsedTime)
{
	//	���W�̎擾
	SimpleMath::Vector2 pos = m_cloud->GetPosition();
	//	���W�̈ړ�
	pos.x -= elapsedTime * MOVE_SPEED;

	//	�����x�̎擾
	float alpha = m_cloud->GetAlpha();
	//	�����x�̍X�V
	alpha += elapsedTime / 2.0f;


	//	���[�U�[���\�[�X�̎擾
	auto ur = UserResources::GetInstance();
	//	�����x�ŉ��ʐݒ�
	float volume =ur->Lerp(AudioResources::MAX_VOLUME, 0.0f, alpha);
	//	���ʂ̐ݒ�
	ur->GetAudioEngine()->SetMasterVolume(volume);

	//	�����x�̐ݒ�
	m_cloud->SetAlpha(alpha);
	m_white->SetAlpha(alpha);

	//	�ړ��̏I������
	if (pos.x <= FADE_IN_START_POSITION.x)
	{
		//	���W�̐ݒ�
		pos.x = FADE_IN_START_POSITION.x;
		m_cloud->SetPosition(pos);

		//	�����x�̐ݒ�
		m_cloud->SetAlpha(1.0f);
		m_white->SetAlpha(1.0f);
		//	���ʂ̐ݒ�
		ur->GetAudioEngine()->SetMasterVolume(0.0f);

		//	�t�F�C�h�A�E�g�̏I��
		return true;
	}

	//	���W�̐ݒ�
	m_cloud->SetPosition(pos);
	return false;
}

/// <summary>
/// �`��
/// </summary>
void FadeCloud::Render()
{
	//	�_�摜�̕`��
	m_cloud->Render();
	//	�����摜�̕`��
	m_white->Render();
}