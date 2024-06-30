//--------------------------------------------------------------------------------------
// File: PredictionLine.h
//
// �\�����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PREDICTION_LINE_DEFINED
#define PREDICTION_LINE_DEFINED

#include "GameObjects/Object.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

/// <summary>
/// �\�����N���X
/// </summary>
class PredictionLine
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PredictionLine();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PredictionLine();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset ();

	/// <summary>
	/// ���W�̒ǉ�
	/// </summary>
	/// <param name="pos">���W</param>
	void AddPosition(const DirectX::SimpleMath::Vector3& pos) { m_poses.push_back(pos); }

	/// <summary>
	/// �A�N�e�B�u��Ԃ̐ݒ�
	/// </summary>
	/// <param name="flag">�A�N�e�B�u���</param>
	void SetIsActive(const bool& flag) { m_isActive = flag; }
	/// <summary>
	/// �A�N�e�B�u��Ԃ̎擾
	/// </summary>
	/// <returns>�A�N�e�B�u���</returns>
	const bool GetIsActive() { return m_isActive; }

public:
	static const float PREDICTION_TIME;

private:
	//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
	const static DirectX::VertexPositionTexture VERTICES[4];

	// ���̓��C�A�E�g�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �e�N�X�`���n���h�� �̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �G�t�F�N�g �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�` �̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//	�p�[�e�B�N�����Ƃ̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_poses;
	//	�A�N�e�B�u���
	bool m_isActive;
};
#endif // !JUMP_PARTICLE_DEFINED
