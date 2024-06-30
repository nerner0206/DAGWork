//--------------------------------------------------------------------------------------
// File: StageFactory.h
//
// �X�e�[�W�t�@�N�g���[�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef STAGE_FACTORY_DEFINED
#define STAGE_FACTORY_DEFINED

#include "GameObjects/PlayScene/StageObjects/Factory/IStageFactory.h"

class StageFactory : public IStageFactory
{
public:
	/// <summary>
	/// �S�[���̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>�S�[���N���X�̃��j�[�N�|�C���^</returns>
	static std::unique_ptr<Goal> CreateGoal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);

	/// <summary>
	/// ����̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>����N���X�̃|�C���^</returns>
	static Ground* CreateGround(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);

	/// <summary>
	/// ��������̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="speed">�ړ����x</param>
	/// <returns>��������N���X�̃|�C���^</returns>
	static MoveGround* CreateMoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed);

	/// <summary>
	/// ���̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="power">����</param>
	/// <returns>���N���X�̃|�C���^</returns>
	static std::unique_ptr<Wind> CreateWind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power);

	/// <summary>
	/// ���D�̐���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>���D�N���X�̃|�C���^</returns>
	static Balloon* CreateBalloon(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
};
#endif // !STAGE_FACTORY_DEFINED
