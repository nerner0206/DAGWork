//--------------------------------------------------------------------------------------
// File: SystemSelectUI.h
//
// �Z���N�g�ݒ�UI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_SELECT_UI_DEFINED
#define SYSTEM_SELECT_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

/// <summary>
/// �Z���N�g�ݒ�UI�N���X
/// </summary>
class SystemSelectUI : public SystemUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SystemSelectUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SystemSelectUI();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
	/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
	void Update(IScene* scene, SystemWindow* window) override;
	/// <summary>
	/// �`��
	/// </summary>
	void Render() override;
};
#endif // !SYSTEM_SELECT_UI_DEFINED