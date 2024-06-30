//--------------------------------------------------------------------------------------
// File: IObject.h
//
// �I�u�W�F�N�g�C���^�[�t�F�[�X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef IOBJECT_DEFINED
#define IOBJECT_DEFINED

#include "MyLib/UserResources.h"
#include "MyLib/AudioResources.h"
#include "Game/DataPath.h"

/// <summary>
/// �I�u�W�F�N�g�C���^�[�t�F�[�X
/// </summary>
interface IObject
{
	/// <summary>
	/// ���[�U�[���\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	virtual UserResources* GetUserResources() = 0;
	/// <summary>
	/// �����\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>�����\�[�X�N���X�̃|�C���^</returns>
	virtual AudioResources* GetAudioResources() = 0;

	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~IObject() = default;

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	virtual const DirectX::SimpleMath::Vector3 GetPos() = 0;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	virtual void SetPos(const DirectX::SimpleMath::Vector3& pos) = 0;

	/// <summary>
	/// ��]�N�H�[�^�j�I���̎擾
	/// </summary>
	/// <returns>��]�N�H�[�^�j�I��</returns>
	virtual const DirectX::SimpleMath::Quaternion GetRotQua() = 0;
	/// <summary>
	/// ��]�N�H�[�^�j�I���̐ݒ�
	/// </summary>
	/// <param name="rotQua">��]�N�H�[�^�j�I��</param>
	virtual void SetRotQua(const DirectX::SimpleMath::Quaternion& rotQua) = 0;

	/// <summary>
	/// �g�嗦�̎擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	virtual const DirectX::SimpleMath::Vector3 GetSca() = 0;
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="sca">�g�嗦</param>
	virtual void SetSca(const DirectX::SimpleMath::Vector3& sca) = 0;
};
#endif // !IOBJECT_DEFINED
