//--------------------------------------------------------------------------------------
// File: SpringStateShrink.cpp
//
// �v���C���[�΂˂̒ʏ��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringStateShrink.h"

#include "SpringStateDefault.h"

using namespace DirectX;

/// <summary>
///	�R���X�g���N�^
/// </summary>
/// <param name="spring">�v���C���[�΂˃N���X�̃|�C���^</param>
SpringStateShrink::SpringStateShrink(PlayerSpring* spring) :
	SpringState(spring)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpringStateShrink::~SpringStateShrink()
{

}

/// <summary>
/// ������
/// </summary>
void SpringStateShrink::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void SpringStateShrink::Update(const float& elapsedTime)
{
	//	�g�嗦�̎擾
	SimpleMath::Vector3 sca = GetSpring()->GetSca();

	//	�k������
	sca.y *= GetSpring()->GetShrinkRatio();

	//	�k�ݐ؂�����
	if (sca.y < 0.5f)
	{
		//	�T�C�Y���Œ�l�֖߂�
		sca.y = 0.5f;
		//	�g�嗦�̐ݒ�
		GetSpring()->SetSca(sca);

		//	�k�ݒ�����������
		GetSpring()->SetIsShrink(false);

		//	���˕Ԃ鑬�x
		SimpleMath::Vector3 vel = SimpleMath::Vector3::Transform(
			SimpleMath::Vector3(0.0f, GetSpring()->GetJumpForce(), 0.0f), GetSpring()->GetRotQua());
		//	���x�̐ݒ�
		GetSpring()->SetVelocity(vel);

		//	�W�����v���̍Đ�
		GetSpring()->GetAudioResources()->PlayJumpSE();

		//	���D�̔j��
		GetSpring()->BreakBalloon();

		//	��Ԃ�ʏ��Ԃ�
		GetSpring()->SetNextState(new SpringStateDefault(GetSpring()));
		return;
	}

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
	//	�g�嗦�̐ݒ�
	GetSpring()->SetSca(sca);
}

/// <summary>
/// �I��
/// </summary>
void SpringStateShrink::Finalize()
{

}