//--------------------------------------------------------------------------------------
// File: Cloud.h
//
// �_�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef CLOUD_DEFINED
#define CLOUD_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// �_�N���X
/// </summary>
class Cloud : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Cloud();
	/// <summary>
	///	�f�X�g���N�^
	/// </summary>
	~Cloud();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="filePath">�_���f���̃t�@�C���p�X</param>
	void Initialize(const wchar_t* filePath);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

private:
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//	���f���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;
};
#endif // !CLOUD_DEFINED