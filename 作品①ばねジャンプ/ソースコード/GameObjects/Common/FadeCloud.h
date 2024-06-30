//--------------------------------------------------------------------------------------
// File: FadeCloud.h
//
// �t�F�C�h�p�_�摜�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef FADE_CLOUD_DEFINED
#define FADE_CLOUD_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// �t�F�C�h�p�_�摜�N���X
/// </summary>
class FadeCloud
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FadeCloud();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FadeCloud();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �t�F�C�h�C��������
	/// </summary>
	void FadeInStart();
	/// <summary>
	/// �t�F�C�h�C���X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <returns>�I������</returns>
	bool FadeInUpdate(const float& elapsedTime);

	/// <summary>
	/// �t�F�C�h�A�E�g������
	/// </summary>
	void FadeOutStart();
	/// <summary>
	/// �t�F�C�h�A�E�g�X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <returns>�I������</returns>
	bool FadeOutUpdate(const float& elapsedTime);

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

private:
	//	�����摜�̊g�嗦
	static const float WHITE_SCALE;
	//	�ړ����x
	static const float MOVE_SPEED;

	//	�t�F�C�h�C���������W
	static const DirectX::SimpleMath::Vector2 FADE_IN_START_POSITION;

private:
	//	�_�摜�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_cloud;
	//	�����摜�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_white;
};
#endif // !FADE_CLOUD_DEFINED
