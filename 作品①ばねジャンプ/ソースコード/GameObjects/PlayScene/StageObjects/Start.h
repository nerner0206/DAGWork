//--------------------------------------------------------------------------------------
// File: Start.h
//
// �X�^�[�g�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef START_DEFINED
#define START_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// �X�^�[�g�N���X
/// </summary>
class Start : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Start();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Start();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">���W</param>
	void Initialize();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	void DebugRender();
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

public:
	//	�J�n���W
	static const DirectX::SimpleMath::Vector3 START_POSITION;

private:
	//	���f��
	std::unique_ptr<DirectX::Model> m_model;

	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
};
#endif // !Start_DEFINED