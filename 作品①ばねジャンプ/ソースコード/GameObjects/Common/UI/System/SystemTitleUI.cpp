//--------------------------------------------------------------------------------------
// File: SystemTitleUI.h
//
// �^�C�g���ݒ�UI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemTitleUI.h"

#include "Scenes/TitleScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SystemTitleUI::SystemTitleUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos) :
	SystemUI(fileName, pos)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SystemTitleUI::~SystemTitleUI()
{

}

/// <summary>
/// ������
/// </summary>
void SystemTitleUI::Initialize()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
void SystemTitleUI::Update(IScene* scene, SystemWindow* window)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	�G���^�[�L�[�Ń^�C�g���V�[����
	if (kbTracker->pressed.Space)
	{
		//	���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�^�C�g���V�[����
		scene->GetSceneManager()->SetNextScene(new TitleScene());
		//	�ݒ��ʂ����
		window->OffWindow(scene);
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
void SystemTitleUI::Render()
{
	//	UI�̕`��
	GetImage()->Render();
}