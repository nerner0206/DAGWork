//--------------------------------------------------------------------------------------
// File: CounterUI.h
//
// �J�E���^�[UI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef COUNTER_UI_DEFINED
#define COUNTER_UI_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// �X�y�[�XUI�N���X
/// </summary>
class CounterUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CounterUI();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CounterUI();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	/// <summary>
	/// �`��
	/// </summary>
	void Render(const int& count);

private:
	//	�񌅖ڂ̍��W�̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector2 FIRST_OFFSET;
	//	�񌅖ڂ̍��W�̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector2 SECOND_OFFSET;
	//	�O���ڂ̍��W�̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector2 THIRD_OFFSET;
	//	�l���ڂ̍��W�̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector2 FOURTH_OFFSET;

private:
	//	���S���W
	DirectX::SimpleMath::Vector2 m_centerPos;

	//	�ꌅ�ڂ̍��W
	DirectX::SimpleMath::Vector2 m_firstPos;
	//	�񌅖ڂ̍��W
	DirectX::SimpleMath::Vector2 m_secondPos;
	//	�O���ڂ̍��W
	DirectX::SimpleMath::Vector2 m_thirdPos;
	//	�l���ڂ̍��W
	DirectX::SimpleMath::Vector2 m_fourthPos;

	//	����UI�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<UserInterface>> m_numbersUI;

	//	���S�A�C�R��UI�̃��j�[�N�|�C���^�z��
	std::unique_ptr<UserInterface> m_centerUI;
};
#endif // !COUNTER_UI_DEFINED