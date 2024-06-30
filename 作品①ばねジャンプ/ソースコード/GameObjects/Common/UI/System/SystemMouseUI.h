//--------------------------------------------------------------------------------------
// File: SystemMouseUI.h
//
// �}�E�X���x�ݒ�UI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_MOUSE_UI_DEFINED
#define SYSTEM_MOUSE_UI_DEFINED

#include "GameObjects/Common/UI/SystemUI.h"

#include <vector>

/// <summary>
/// �}�E�X���x�ݒ�UI�N���X
/// </summary>
class SystemMouseUI : public SystemUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SystemMouseUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos, const int& num);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SystemMouseUI();

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

	/// <summary>
	/// �}�E�X���x�ԍ��̐ݒ�
	/// </summary>
	/// <param name="num">�}�E�X���x�ԍ�</param>
	void SetMouseNumber(const int& num) { m_moveNum = num; }
	/// <summary>
	/// �}�E�X���x�ԍ��̎擾
	/// </summary>
	/// <returns>�}�E�X���x�ԍ�</returns>
	const int GetMouseNumber() { return m_moveNum; }

private:
	//	�ԍ��̊Ԋu
	static const int NUM_DISTANCE = 30;

	//	�ԍ��̊���W
	static const DirectX::SimpleMath::Vector2 NUM_POSITION;

private:
	//	�I��ԍ�
	int m_moveNum;

	//	�ԍ�UI�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<UserInterface>> m_numUIs;
	//	�I���t���[��UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_frame;
};
#endif // !SYSTEM_MOUSE_UI_DEFINED