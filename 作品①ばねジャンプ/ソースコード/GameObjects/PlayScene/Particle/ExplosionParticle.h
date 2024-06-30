//--------------------------------------------------------------------------------------
// File: ExplosionParticle.h
//
// �����p�[�e�B�N���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef EXPLOSION_PARTICLE_DEFINED
#define EXPLOSION_PARTICLE_DEFINED

#include "Particle.h"

/// <summary>
/// �����p�[�e�B�N���N���X
/// </summary>
class ExplosionParticle : public Particle
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ExplosionParticle();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ExplosionParticle();

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
	static const DirectX::VertexPositionTexture VERTICES[4];
	//	�g�嗦
	static const float MAX_SCALE;

private:
	// ���̓��C�A�E�g�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �e�N�X�`���n���h�� �̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textures[DataPath::EXPLOSION_PARTICLE_IMAGE_NUM];
	// �G�t�F�N�g �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�` �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//  �^�C�}�[
	float m_timer;
	//	�摜�ԍ�
	int m_texNum;
};
#endif // !JUMP_PARTICLE_DEFINED
