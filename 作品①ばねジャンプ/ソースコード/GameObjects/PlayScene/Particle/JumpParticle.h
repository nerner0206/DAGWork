//--------------------------------------------------------------------------------------
// File: JumpParticle.h
//
// �W�����v�p�[�e�B�N���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef JUMP_PARTICLE_DEFINED
#define JUMP_PARTICLE_DEFINED

#include "Particle.h"

/// <summary>
/// �_�p�[�e�B�N���N���X
/// </summary>
class JumpParticle : public Particle
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	JumpParticle();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~JumpParticle();

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
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �p�[�e�B�N���̎��s
	/// </summary>
	/// <param name="pos">���W</param>
	void Play(const DirectX::SimpleMath::Vector3& pos) override;
	/// <summary>
	/// �p�[�e�B�N���̒�~
	/// </summary>
	void Stop() override;

private:
	//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
	const static DirectX::VertexPositionTexture VERTICES[4];
	//	�p�[�e�B�N���̐�
	const static int PARTICLE_NUMBER = 8;

	// ���̓��C�A�E�g�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �e�N�X�`���n���h�� �̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �G�t�F�N�g �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�` �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//	�p�[�e�B�N�����Ƃ̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_particlePos;
	//	�p�[�e�B�N�����Ƃ̑��x
	std::vector<DirectX::SimpleMath::Vector3> m_particleVel;

	//  �^�C�}�[
	float m_timer;
};
#endif // !JUMP_PARTICLE_DEFINED
