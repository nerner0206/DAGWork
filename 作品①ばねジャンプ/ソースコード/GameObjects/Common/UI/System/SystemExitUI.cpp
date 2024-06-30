//--------------------------------------------------------------------------------------
// File: SystemExitUI.h
//
// �I���ݒ�UI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemExitUI.h"

#include "MyLib/IScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SystemExitUI::SystemExitUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SystemExitUI::~SystemExitUI()
{

}

/// <summary>
/// ������
/// </summary>
void SystemExitUI::Initialize()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
void SystemExitUI::Update(IScene* scene, SystemWindow* window)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	
	//	�G���^�[�L�[�ŏI��
	if (kbTracker->pressed.Space)
	{
		//	���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�Q�[���̏I��
		PostQuitMessage(0);
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
void SystemExitUI::Render()
{
	//	UI�̕`��
	GetImage()->Render();
}