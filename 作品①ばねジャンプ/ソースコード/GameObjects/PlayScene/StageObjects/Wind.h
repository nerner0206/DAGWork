//--------------------------------------------------------------------------------------
// File: Wind.h
//
// ���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef WIND_DEFINED
#define WIND_DEFINED

#include "GameObjects/PlayScene/StageObjects/IStageObject.h"

class Player;
class Particle;

/// <summary>
/// ���N���X
/// </summary>
class Wind : public IStageObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="power">����</param>
	Wind(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca,
		const float& power);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Wind();

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
	void Reset() override;

	/// <summary>
	/// ���̌����̎擾
	/// </summary>
	/// <returns>���̌���</returns>
	const DirectX::SimpleMath::Vector3 GetVector() { return m_vector; }
	/// <summary>
	/// ���͂̎擾
	/// </summary>
	/// <returns>����</returns>
	const float GetPower() { return m_power; }

	/// <summary>
	/// �v���C���[�̐ݒ�
	/// </summary>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	void SetPlayer(Player* player) { m_player = player; }

public:
	//	�f�[�^�A�N�Z�X�p������
	static const std::string POWER_STR;

private:
	//	���̕���
	DirectX::SimpleMath::Vector3 m_vector;
	//	����
	float m_power;

	//	���̏Փ˔���
	bool m_isHit;

	//	�v���C���[�N���X�̃|�C���^
	Player* m_player;

	//	���p�[�e�B�N���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Particle> m_windParticle;
};
#endif // !WIND_DEFINED