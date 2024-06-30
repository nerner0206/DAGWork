//--------------------------------------------------------------------------------------
// File: PlayerSpring.h
//
// �v���C���[�΂˃N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_SPRING_DEFINED
#define PLAYER_SPRING_DEFINED

#include "Player.h"
#include "SpringState/SpringState.h"
#include "MyLib/JsonManager.h"

class SpringPart;
class PredictionLine;
class Balloon;

/// <summary>
/// �v���C���[�΂˃N���X
/// </summary>
class PlayerSpring : public PlayerComponent
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="p">�v���C���[�N���X�̃|�C���^</param>
	PlayerSpring(Player* p);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerSpring();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	/// <param name="stageObjects">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		StageManager* stageManager) override;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
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
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	void Reset(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) override;
	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	void SaveData() override;

	/// <summary>
	/// �e�X�g�X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void TestUpdate(const float& elapsedTime);

	/// <summary>
	/// ���̏�Ԃ̐ݒ�
	/// </summary>
	/// <param name="state">�΂ˏ�ԃN���X�̃|�C���^</param>
	void SetNextState(SpringState* state);

	/// <summary>
	///	���D�̔j��
	/// </summary>
	void BreakBalloon();

	/// <summary>
	/// ���x�̎擾
	/// </summary>
	/// <returns>���x�x�N�g��</returns>
	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }
	/// <summary>
	/// ���x�̐ݒ�
	/// </summary>
	/// <param name="vel">���x�x�N�g��</param>
	void SetVelocity(const DirectX::SimpleMath::Vector3& vel) { m_velocity = vel; }
	/// <summary>
	/// ���x�̉��Z
	/// </summary>
	/// <param name="vel">���x�x�N�g��</param>
	void AddVelocity(const DirectX::SimpleMath::Vector3& vel) { m_velocity += vel; }

	/// <summary>
	/// �k�ݒ��̎擾
	/// </summary>
	/// <returns>�k�ݒ�</returns>
	const bool GetIsShrink() { return m_isShrink; }
	/// <summary>
	/// �k�ݒ��̐ݒ�
	/// </summary>
	/// <param name="isShrink">�k�ݒ�</param>
	void SetIsShrink(const bool& isShrink) { m_isShrink = isShrink; }

	/// <summary>
	/// �d�͂̎擾
	/// </summary>
	/// <returns>�d��</returns>
	const float GetGravity() { return m_gravity; }
	/// <summary>
	/// �W�����v�͂̎擾
	/// </summary>
	/// <returns>�W�����v��</returns>
	const float GetJumpForce() { return m_jumpForce; }

	/// <summary>
	/// �k�ޕω����̎擾
	/// </summary>
	/// <returns>�k�ޕω���</returns>
	const float GetShrinkRatio() { return m_shrinkRatio; }
	/// <summary>
	/// �L�т鑬�x�̎擾
	/// </summary>
	/// <returns>�L�т鑬�x</returns>
	const float GetExtendSpeed() { return m_extendSpeed; }

	/// <summary>
	/// �S�[������̎擾
	/// </summary>
	/// <returns>�S�[������</returns>
	const bool GetIsGoal() { return m_isGoal; }
	/// <summary>
	/// �S�[������̐ݒ�
	/// </summary>
	/// <param name="isGoal">�S�[������</param>
	void SetIsGoal(const bool& isGoal) { m_isGoal = isGoal; }

public:
	//	�f�[�^�̐�
	static const int DATA_NUMBER = 5;
	//	�f�[�^�A�N�Z�X������z��
	static const std::string DATA_STRING[DATA_NUMBER];

	//	�����蔻��̔��a
	static const float COLLISION_RADIUS;
	//	���̓����蔻��̍��W
	static const DirectX::SimpleMath::Vector3 COLLISION_POSITION_OFFSET;
	//	���̍��W
	static const DirectX::SimpleMath::Vector3 HEAD_POSITION_OFFSET;

private:
	//	json�t�@�C��
	nlohmann::json m_springData;

	//	�v���C���[���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<PlayerComponent> m_head;

	//	�΂ˏ�ԃN���X�̃|�C���^
	SpringState* m_nowSpringState;
	//	���̂΂ˏ�ԃN���X�̃|�C���^
	SpringState* m_nextSpringState;

	//	���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//	�k�ݒ�
	bool m_isShrink;

	//	�d��
	float m_gravity;
	//	�W�����v��
	float m_jumpForce;

	//	�k�ޕω���
	float m_shrinkRatio;
	//	�L�т鑬�x
	float m_extendSpeed;

	//	���̗�
	float m_XZForceRatio;

	//	�O�t���[���̃}�E�X���W
	DirectX::SimpleMath::Vector2 m_oldMousePos;

	//	�ڐG�������D
	Balloon* m_hitBalloon;

	//	�΂˂̃p�[�c�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<SpringPart>> m_springParts;

	//	�Փˈʒu
	DirectX::SimpleMath::Vector3 m_hitPos;

	//	�S�[������
	bool m_isGoal;

	//	�\�����N���X�̃��j�[�N�|�C���^
	std::unique_ptr<PredictionLine> m_line;

private:
	/// <summary>
	/// ��Ԃ̐ݒ�
	/// </summary>
	/// <param name="state">�΂ˏ�ԃN���X�̃|�C���^</param>
	void SetState(SpringState* state);
	/// <summary>
	/// ��Ԃ̍폜
	/// </summary>
	void DeleteState();

	/// <summary>
	/// ��]�X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void RotUpdate(const float& elapsedTime);
	/// <summary>
	/// �߂荞�ݕ␳
	/// </summary>
	/// <param name="distance">�߂荞�ݗ�</param>
	/// <returns>�␳�x�N�g��</returns>
	DirectX::SimpleMath::Vector3 InImmersed(const float& distance);

	/// <summary>
	/// �\�����\���̐؂�ւ�
	/// </summary>
	void ChangeDisplayLine();
	/// <summary>
	///	�\�����̌v�Z
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void PreLine(const float& elapsedTime);
};
#endif // !PLAYER_SPRING_DEFINED