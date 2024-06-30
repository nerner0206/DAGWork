//--------------------------------------------------------------------------------------
// File: IStageFactory.h
//
// �X�e�[�W�t�@�N�g���[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISTAGE_FACTORY_DEFINED
#define ISTAGE_FACTORY_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"
#include "GameObjects/PlayScene/StageObjects/Goal.h"
#include "GameObjects/PlayScene/StageObjects/MoveGround.h"
#include "GameObjects/PlayScene/StageObjects/Balloon.h"
#include "GameObjects/PlayScene/StageObjects/Wind.h"

/// <summary>
/// �X�e�[�W�t�@�N�g���[���N���X
/// </summary>
class IStageFactory
{
public:
	/// <summary>
	/// �S�[���̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>�S�[���N���X�̃��j�[�N�|�C���^</returns>
	virtual std::unique_ptr<Goal> CreateGoal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;

	/// <summary>
	/// ����̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>����N���X�̃|�C���^</returns>
	virtual Ground* CreateGround(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;

	/// <summary>
	/// ��������̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="speed">�ړ����x</param>
	/// <returns>��������N���X�̃|�C���^</returns>
	virtual MoveGround* CreateMoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed) = 0;

	/// <summary>
	/// ���̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="power">����</param>
	/// <returns>���N���X�̃|�C���^</returns>
	virtual std::unique_ptr<Wind> CreateWind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power) = 0;

	/// <summary>
	/// ���D�̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>���D�N���X�̃|�C���^</returns>
	virtual Balloon* CreateBalloon(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) = 0;
};
#endif // !ISTAGE_FACTORY_DEFINED
