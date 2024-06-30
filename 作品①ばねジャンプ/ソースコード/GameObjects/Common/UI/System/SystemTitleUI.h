//--------------------------------------------------------------------------------------
// File: SystemTitleUI.h
//
// �^�C�g���ݒ�UI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_TITLE_UI_DEFINED
#define SYSTEM_TITLE_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

/// <summary>
/// �^�C�g���ݒ�UI�N���X
/// </summary>
class SystemTitleUI : public SystemUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SystemTitleUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SystemTitleUI();

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
#endif // !SYSTEM_TITLE_UI_DEFINED