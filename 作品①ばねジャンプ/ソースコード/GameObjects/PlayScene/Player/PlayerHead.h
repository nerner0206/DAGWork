//--------------------------------------------------------------------------------------
// File: PlayerHead.h
//
// �v���C���[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_HEAD_DEFINED
#define PLAYER_HEAD_DEFINED

#include "Player.h"

/// <summary>
/// �v���C���[���N���X
/// </summary>
class PlayerHead : public PlayerComponent
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="p">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="parent">�e�̃|�C���^</param>
	PlayerHead(Player* p, PlayerComponent* parent);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerHead();

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
	/// �Փ˂̎擾
	/// </summary>
	/// <returns>�Փ˔���</returns>
	bool GetHit() const { return m_hit; }
	/// <summary>
	/// �Փ˂̐ݒ�
	/// </summary>
	/// <param name="hit">�Փ˔���</param>
	void SetHit(const bool& hit) { m_hit = hit; }

public:
	//	���̃f�t�H���g�T�C�Y
	const static DirectX::SimpleMath::Vector3 PLAYER_HEAD_SIZE;

private:
	//	���f���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;
	//	�Փ˔���
	bool m_hit;
};
#endif // !PLAYER_HEAD_DEFINED