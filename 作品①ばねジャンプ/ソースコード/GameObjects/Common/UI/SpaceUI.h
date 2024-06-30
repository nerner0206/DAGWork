//--------------------------------------------------------------------------------------
// File: SpaceUI.h
//
// �X�y�[�XUI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPACE_UI_DEFINED
#define SPACE_UI_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// �X�y�[�XUI�N���X
/// </summary>
class SpaceUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SpaceUI();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SpaceUI();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// �`��
	/// </summary>
	void Render();

private:
	//	�X�y�[�X�P�摜
	std::unique_ptr<UserInterface> m_Space_01;
	//	�X�y�[�X�Q�摜
	std::unique_ptr<UserInterface> m_Space_02;

	//	�J�E���g
	int count;
};
#endif // !SPACE_UI_DEFINED