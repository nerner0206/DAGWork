//--------------------------------------------------------------------------------------
// File: Object.h
//
// �I�u�W�F�N�g���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef OBJECT_DEFINED
#define OBJECT_DEFINED

#include "IObject.h"

/// <summary>
/// �I�u�W�F�N�g���N���X
/// </summary>
class Object : public IObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rotQua">��]�N�H�[�^�j�I��</param>
	/// <param name="sca">�g�嗦</param>
	Object(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotQua,
		const DirectX::SimpleMath::Vector3& sca) :
		m_pos(pos), m_rotQua(rotQua), m_sca(sca)
	{
		//	���[�U�[���\�[�X�̎擾
		m_ur = UserResources::GetInstance();
		//	�����\�[�X�N���X�̎擾
		m_ar = AudioResources::GetInstance();
	}

	/// <summary>
	/// ���[�U�[���\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	UserResources* GetUserResources() override { return m_ur; }
	/// <summary>
	/// �����\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>�����\�[�X�N���X�̃|�C���^</returns>
	AudioResources* GetAudioResources() override { return m_ar; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const DirectX::SimpleMath::Vector3 GetPos() override { return m_pos; }
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPos(const DirectX::SimpleMath::Vector3& pos) override { m_pos = pos; }

	/// <summary>
	/// ��]�N�H�[�^�j�I���̎擾
	/// </summary>
	/// <returns>��]�N�H�[�^�j�I��</returns>
	const DirectX::SimpleMath::Quaternion GetRotQua() override { return m_rotQua; }
	/// <summary>
	/// ��]�N�H�[�^�j�I���̐ݒ�
	/// </summary>
	/// <param name="rotQua">��]�N�H�[�^�j�I��</param>
	void SetRotQua(const DirectX::SimpleMath::Quaternion& rotQua) override { m_rotQua = rotQua; }

	/// <summary>
	/// �g�嗦�̎擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const DirectX::SimpleMath::Vector3 GetSca() override { return m_sca; }
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="sca">�g�嗦</param>
	void SetSca(const DirectX::SimpleMath::Vector3& sca) override { m_sca = sca; }

public:
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~Object() = default;

private:
	//	���[�U�[���\�[�X�N���X�̃|�C���^
	UserResources* m_ur;
	//	�����\�[�X�N���X�̃|�C���^
	AudioResources* m_ar;

	//	���W
	DirectX::SimpleMath::Vector3 m_pos;
	//	��]�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotQua;
	//	�g�嗦
	DirectX::SimpleMath::Vector3 m_sca;
};
#endif // !OBJECT_DEFINED
