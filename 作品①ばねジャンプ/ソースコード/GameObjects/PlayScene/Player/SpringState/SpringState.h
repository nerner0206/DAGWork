//--------------------------------------------------------------------------------------
// File: SpringState.h
//
// �v���C���[�΂ˏ�ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPRING_STATE_DEFINED
#define SPRING_STATE_DEFINED

class PlayerSpring;

class SpringState
{
public:
	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	/// <param name="spring">�v���C���[�΂˃N���X�̃|�C���^</param>
	SpringState(PlayerSpring* spring) :
		m_spring(spring) { }

	/// <summary>
	/// �v���C���[�΂˃N���X�̎擾
	/// </summary>
	/// <returns>�v���C���[�΂˃N���X�̃|�C���^</returns>
	PlayerSpring* GetSpring() { return m_spring; }

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SpringState() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;

private:
	//	�v���C���[�΂˃N���X�̃|�C���^
	PlayerSpring* m_spring;
};
#endif // !SPRING_STATE_DEFINED