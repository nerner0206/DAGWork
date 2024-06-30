//--------------------------------------------------------------------------------------
// File: Ground.h
//
// ����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GROUND_DEFINED
#define GROUND_DEFINED

#include "GameObjects/PlayScene/StageObjects/IStageObject.h"

/// <summary>
/// ����N���X
/// </summary>
class Ground : public IStageObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	Ground(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Ground();

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
	/// �h�ꔻ��̐ݒ�
	/// </summary>
	/// <param name="flag">�h�ꔻ��</param>
	void SetIsShake(const bool& flag) { m_isShake = flag; }

public:
	/// <summary>
	///	�h���
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Shaking(const float& elapsedTime);

private:
	//	�f�t�H���g�g�嗦
	DirectX::SimpleMath::Vector3 m_defSca;
	//	�_�̗h��g�嗦
	DirectX::SimpleMath::Vector3 m_targetSca;

	//	�_�̗h�ꔻ��
	bool m_isShake;
	//	�^�C�}�[
	float m_t;
};
#endif // !GROUND_DEFINED