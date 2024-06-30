//--------------------------------------------------------------------------------------
// File: Player.h
//
// �v���C���[�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

#include "PlayerComponent.h"

class Particle;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="startPos">�������W</param>
	void Initialize(const DirectX::SimpleMath::Vector3& startPos);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="stageObjs">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	void Update(const float& elapsedTime, StageManager* stageManager);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	void DebugRender();
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();
	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	void SaveData();

	/// <summary>
	/// �}�E�X���x�̎擾
	/// </summary>
	/// <returns>�}�E�X���x</returns>
	const float GetMouseSensitivity() { return m_mouseSensitivity; }
	/// <summary>
	/// �}�E�X���x�̐ݒ�
	/// </summary>
	/// <param name="mouseSensitivity">�}�E�X���x</param>
	void SetMouseSensitivity(const float& mouseSensitivity) { m_mouseSensitivity = mouseSensitivity; }

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	/// <returns>�����蔻��N���X�̃|�C���^</returns>
	CollisionObject* GetBoxCollider() { return m_boxCollider.get(); }

	/// <summary>
	/// �΂˂̃|�C���^�̎擾
	/// </summary>
	/// <returns>�v���C���[���i�N���X�̃|�C���^</returns>
	PlayerComponent* GetPlayerSpring() { return m_playerSpring.get(); }

	/// <summary>
	/// �S�[������̎擾
	/// </summary>
	/// <returns>�S�[������t���O</returns>
	const bool GetIsGoal() { return m_isGoal; }

	/// <summary>
	/// ���S����̐ݒ�
	/// </summary>
	/// <param name="flag">���S����t���O</param>
	void SetIsDead(const bool& flag) { m_isDead = flag; }
	/// <summary>
	/// ���S����̎擾
	/// </summary>
	/// <returns></returns>
	const bool GetIsDead() { return m_isDead; }

	/// <summary>
	/// �W�����v�p�[�e�B�N���̎擾
	/// </summary>
	/// <returns>�p�[�e�B�N�����N���X�̃|�C���^</returns>
	Particle* GetJumpParticle() { return m_jumpParticle.get(); }
	/// <summary>
	/// �����p�[�e�B�N���̎擾
	/// </summary>
	/// <returns>�p�[�e�B�N�����N���X�̃|�C���^</returns>
	Particle* GetExplosionParticle() { return m_explosionParticle.get(); }

private:
	//	�����蔻��̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector3 COLLISION_POSITION_OFFSET;
	//	�����蔻��̊g�嗦
	static const DirectX::SimpleMath::Vector3 COLLISION_SCALE;

private:
	//	�v���C���[�΂˃N���X�̃��j�[�N�|�C���^
	std::unique_ptr<PlayerComponent> m_playerSpring;
	//	�v���C���[�S�̂̓����蔻��N���X�̃��j�[�N�|�C���^
	std::unique_ptr<CollisionObject> m_boxCollider;

	//	�������W
	DirectX::SimpleMath::Vector3 m_startPos;

	//	�}�E�X���x
	float m_mouseSensitivity;

	//	�S�[������t���O
	bool m_isGoal;
	//	���S����t���O
	bool m_isDead;

	//	�W�����v�p�[�e�B�N���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Particle> m_jumpParticle;
	//	�����p�[�e�B�N���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Particle> m_explosionParticle;
};
#endif // !PLAYER_DEFINED