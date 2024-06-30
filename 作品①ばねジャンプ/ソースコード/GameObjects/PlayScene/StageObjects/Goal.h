//--------------------------------------------------------------------------------------
// File: Goal.h
//
// �S�[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GOAL_DEFINED
#define GOAL_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"

/// <summary>
/// �S�[���N���X
/// </summary>
class Goal : public Ground
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	Goal(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Goal();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	void DebugRender() override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;
};
#endif // !GOAL_DEFINED