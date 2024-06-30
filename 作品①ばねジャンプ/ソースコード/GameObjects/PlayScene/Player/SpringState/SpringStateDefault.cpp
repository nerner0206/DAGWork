//--------------------------------------------------------------------------------------
// File: SpringStateDefault.cpp
//
// �v���C���[�΂˂̒ʏ��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringStateDefault.h"

using namespace DirectX;

/// <summary>
///	�R���X�g���N�^
/// </summary>
/// <param name="spring">�v���C���[�΂˃N���X�̃|�C���^</param>
SpringStateDefault::SpringStateDefault(PlayerSpring* spring) :
	SpringState(spring)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpringStateDefault::~SpringStateDefault()
{

}

/// <summary>
/// ������
/// </summary>
void SpringStateDefault::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void SpringStateDefault::Update(const float& elapsedTime)
{
	//	�g�嗦�̎擾
	SimpleMath::Vector3 sca = GetSpring()->GetSca();

	//	�΂˂��k��ł���
	if (sca.y < 1.0f)
	{
		//	���X�ɐL�΂�
		sca.y += GetSpring()->GetExtendSpeed();
		if (sca.y > 1.0f) sca.y = 1.0f;
	}

	//	�g�嗦�̐ݒ�
	GetSpring()->SetSca(sca);

	//	���x�̎擾
	SimpleMath::Vector3 vel = GetSpring()->GetVelocity();
	//	���W�̎擾
	SimpleMath::Vector3 pos = GetSpring()->GetPos();

	//	�d�͂̉��Z
	vel.y -= GetSpring()->GetGravity();
	//	���x�̉��Z
	pos += (vel * elapsedTime);

	//	���x�̐ݒ�
	GetSpring()->SetVelocity(vel);
	//	���W�̐ݒ�
	GetSpring()->SetPos(pos);
}

/// <summary>
/// �I��
/// </summary>
void SpringStateDefault::Finalize()
{

}