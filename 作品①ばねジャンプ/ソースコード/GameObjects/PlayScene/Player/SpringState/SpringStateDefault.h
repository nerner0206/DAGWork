//--------------------------------------------------------------------------------------
// File: SpringStateDefault.h
//
// �v���C���[�΂˂̒ʏ��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPRING_STATE_DEFAULT_DEFINED
#define SPRING_STATE_DEFAULT_DEFINED

#include "GameObjects/PlayScene/Player/PlayerSpring.h"

class SpringStateDefault : public SpringState
{
public:
	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	/// <param name="spring">�v���C���[�΂˃N���X�̃|�C���^</param>
	SpringStateDefault(PlayerSpring* spring);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SpringStateDefault();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;
};
#endif // !SPRING_STATE_DEFAULT_DEFINED