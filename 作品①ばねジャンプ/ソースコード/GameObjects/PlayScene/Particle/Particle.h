//--------------------------------------------------------------------------------------
// File: Particle.h
//
// �p�[�e�B�N�����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PARTICLE_DEFINED
#define PARTICLE_DEFINED

#include "GameObjects/Object.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

/// <summary>
/// �p�[�e�B�N�����N���X
/// </summary>
class Particle : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="sca">�g�嗦</param>
	Particle(const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& sca) :
		Object(pos, rot, sca),
		m_isActive(false)
	{

	}

	/// <summary>
	/// �A�N�e�B�u��Ԃ̎擾
	/// </summary>
	/// <returns>�A�N�e�B�u���</returns>
	const bool& GetActive() { return m_isActive; }
	/// <summary>
	/// �A�N�e�B�u��Ԃ̐ݒ�
	/// </summary>
	/// <param name="flag">�A�N�e�B�u���</param>
	void SetActive(const bool& flag) { m_isActive = flag; }
	
public:
	/// <summary>
	///	�f�X�g���N�^
	/// </summary>
	virtual ~Particle() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	///	�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	virtual void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// �p�[�e�B�N���̎��s
	/// </summary>
	/// <param name="pos">���W</param>
	virtual void Play(const DirectX::SimpleMath::Vector3& pos) = 0;
	/// <summary>
	/// �p�[�e�B�N���̒�~
	/// </summary>
	virtual void Stop() = 0;

private:
	//	�A�N�e�B�u���
	bool m_isActive;
};
#endif // !PARTICLE_DEFINED

