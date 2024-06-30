//--------------------------------------------------------------------------------------
// File: StageFactory.cpp
//
// �X�e�[�W�t�@�N�g���[�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StageFactory.h"

/// <summary>
/// �S�[���̐���
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <returns>�S�[���N���X�̃��j�[�N�|�C���^</returns>
std::unique_ptr<Goal> StageFactory::CreateGoal(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	�n�ʂ��쐬
	std::unique_ptr<Goal> goal = std::make_unique<Goal>(pos, rot, sca);
	//	������
	goal->Initialize();
	//	�n��
	return std::move(goal);
}

/// <summary>
/// ����̐���
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <returns>����N���X�̃|�C���^</returns>
Ground* StageFactory::CreateGround(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	�n�ʂ��쐬
	Ground* ground = new Ground(pos, rot, sca);
	//	������
	ground->Initialize();
	//	�n��
	return ground;
}

/// <summary>
/// ��������̐���
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <param name="speed">�ړ����x</param>
/// <returns>��������N���X�̃|�C���^</returns>
MoveGround* StageFactory::CreateMoveGround(
	const std::vector<DirectX::SimpleMath::Vector3>& poses,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& speed)
{
	//	��s�@���쐬
	MoveGround* moveGround = new MoveGround(poses, rot, sca, speed);
	//	������
	moveGround->Initialize();
	//	�Ԃ�
	return moveGround;
}

/// <summary>
/// ���̐���
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <param name="power">����</param>
/// <returns>���N���X�̃|�C���^</returns>
std::unique_ptr<Wind> StageFactory::CreateWind(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& power)
{
	//	�����쐬
	std::unique_ptr<Wind> wind = std::make_unique<Wind>(pos, rot, sca, power);
	//	������
	wind->Initialize();

	//	�Ԃ�
	return std::move(wind);
}

/// <summary>
/// ���D�̐���
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <returns>���D�N���X�̃|�C���^</returns>
Balloon* StageFactory::CreateBalloon(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	���D���쐬
	Balloon* balloon = new Balloon(pos, rot, sca);
	//	������
	balloon->Initialize();
	//	�n��
	return balloon;
}