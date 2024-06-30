//--------------------------------------------------------------------------------------
// File: MoveGround.h
//
// ��������N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef MOVE_GROUND_DEFINED
#define MOVE_GROUND_DEFINED

#include "GameObjects/PlayScene/StageObjects/Ground.h"

/// <summary>
/// ��������N���X
/// </summary>
class MoveGround : public Ground
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="speed">���x</param>
	MoveGround(
		const std::vector<DirectX::SimpleMath::Vector3>& poses,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& speed);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MoveGround();

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
	/// �f�o�b�O�`��
	/// </summary>
	void DebugRender() override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset() override;

	/// <summary>
	/// ���x�̎擾
	/// </summary>
	/// <returns>���x</returns>
	const float GetSpeed() { return m_speed; }

public:
	//	�f�[�^�A�N�Z�X�p������
	static const std::string POSITIONS_STR;
	//	�f�[�^�A�N�Z�X�p������
	static const std::string SPEED_STR;

private:
	//	�ړ�����W
	std::vector<DirectX::SimpleMath::Vector3> m_poses;

	//	���x
	float m_speed;

	//	���W�ԍ�
	int m_num;
	//	���̔ԍ�
	int m_nextNum;

	//	�ڕW����
	float m_time;
	//	�^�C�}�[
	float m_timer;
};
#endif // !MOVE_GROUND_DEFINED