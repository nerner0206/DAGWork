//--------------------------------------------------------------------------------------
// File: SystemSelectUI.h
//
// �Z���N�g�ݒ�UI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemSelectUI.h"

#include "Scenes/SelectScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SystemSelectUI::SystemSelectUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SystemSelectUI::~SystemSelectUI()
{

}

/// <summary>
/// ������
/// </summary>
void SystemSelectUI::Initialize()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
void SystemSelectUI::Update(IScene* scene, SystemWindow* window)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	�G���^�[�L�[�ŃZ���N�g�V�[����
	if (kbTracker->pressed.Space)
	{
		//	���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�Z���N�g�V�[����
		scene->GetSceneManager()->SetNextScene(new SelectScene());
		//	�ݒ��ʂ����
		window->OffWindow(scene);
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
void SystemSelectUI::Render()
{
	//	UI�̕`��
	GetImage()->Render();
}