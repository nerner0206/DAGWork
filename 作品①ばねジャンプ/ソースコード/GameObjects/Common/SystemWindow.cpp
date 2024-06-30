//--------------------------------------------------------------------------------------
// File: SystemWindow.cpp
//
// �ݒ��ʃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemWindow.h"

#include "GameObjects/Common/UI/System/SystemMouseUI.h"
#include "GameObjects/Common/UI/System/SystemSelectUI.h"
#include "GameObjects/Common/UI/System/SystemTitleUI.h"
#include "GameObjects/Common/UI/System/SystemExitUI.h"

#include "Scenes/PlayScene.h"
#include "MyLib/SceneManager.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SystemWindow::SystemWindow() :
	m_isSystemOpen(false),
	m_selectNum(0),
	m_selectMaxNum(DataPath::SYSTEM_SELECT_NUMBER)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SystemWindow::~SystemWindow()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void SystemWindow::Initialize(const int& mouseNumber)
{
	//	�I�����̐���
	CreateUI(mouseNumber);

	//	�I���t���[���̐���
	m_itemFrame = std::make_unique<UserInterface>();
	m_itemFrame->Create(
		DataPath::SYSTEM_FRAME_IMAGE_PATH,
		m_items[0]->GetPos(),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//	�w�i�̐���
	m_back = std::make_unique<UserInterface>();
	m_back->Create(
		DataPath::SYSTEM_BACK_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One,
		ANCHOR::TOP_LEFT);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
void SystemWindow::Update(IScene* scene)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	ESC�L�[�������ꂽ��ݒ��ʂ̏I��
	if (kbTracker->pressed.Escape)
	{
		OffWindow(scene);
		return;
	}

	//	�㉺�ړ�
	if (kbTracker->pressed.Up && m_selectNum > 0)
	{
		//	�ݒ艹�̍Đ�
		AudioResources::GetInstance()->PlaySelectSE();
		//	�I��ԍ��̍X�V
		m_selectNum--;
	}
	else if (kbTracker->pressed.Down && m_selectNum < m_selectMaxNum - 1)
	{
		//	�ݒ艹�̍Đ�
		AudioResources::GetInstance()->PlaySelectSE();
		//	�I��ԍ��̍X�V
		m_selectNum++;
	}

	//	�t���[���̈ړ�
	MoveFrame();

	//	�e�I�����̍X�V
	m_items[m_selectNum]->Update(scene, this);
}

/// <summary>
/// �`��
/// </summary>
void SystemWindow::Render()
{
	//	�w�i�̕`��
	m_back->Render();

	//	�e�I�����̕`��
	for (auto& item : m_items)
	{
		item->Render();
	}

	//	�I���t���[���̕`��
	m_itemFrame->Render();
}

/// <summary>
/// �I��
/// </summary>
void SystemWindow::Finalize() 
{

}

/// <summary>
/// �ݒ��ʂ̊J�n
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
void SystemWindow::OnWindow(IScene* scene)
{
	//	�ݒ艹�̍Đ�
	AudioResources::GetInstance()->PlaySystemSE();

	//	�J����Ԃ�
	m_isSystemOpen = true;

	//	�I�����ԍ��̏�����
	m_selectNum = 0;
}

/// <summary>
/// �ݒ��ʂ̏I��
/// </summary>
/// <param name="scene">�V�[���N���X�̃|�C���^</param>
void SystemWindow::OffWindow(IScene* scene)
{
	//	�ݒ艹�̍Đ�
	AudioResources::GetInstance()->PlaySystemSE();

	//	�����Ԃ�
	m_isSystemOpen = false;

	//	�}�E�X���x�̔ԍ��̎擾
	SystemMouseUI* mouseUI = dynamic_cast<SystemMouseUI*>(m_items[0].get());
	int m_num = mouseUI->GetMouseNumber();

	//	�V�X�e���ݒ�̕ۑ�
	scene->GetSceneManager()->SaveSystem(m_num);

	//	�v���C�V�[���̏ꍇ�A�����Ɋ��x��ݒ肷��
	if (scene->GetSceneKind() != IScene::SceneKind::PlayScene) return;

	//	�v���C�V�[���փL���X�g
	PlayScene* play = dynamic_cast<PlayScene*>(scene);
	//	���x�̐ݒ�
	play->SetMouseSpeed(m_num);
}

/// <summary>
/// �I���t���[���𓮂���
/// </summary>
void SystemWindow::MoveFrame()
{
	SimpleMath::Vector2 pos = m_items[m_selectNum]->GetPos();
	m_itemFrame->SetPosition(pos);
}

/// <summary>
/// �eUI�̐���
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void SystemWindow::CreateUI(const int& mouseNumber)
{
	//	�y���W
	float y = UserResources::WINDOW_HEIGHT / 2 - ITEM_DISTANCE * (DataPath::SYSTEM_SELECT_NUMBER / 2);
	//	���W
	SimpleMath::Vector2 pos = SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, y + ITEM_DISTANCE);

	//	�e�I�����̐���
	m_items.push_back(std::make_unique<SystemMouseUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[0], pos, mouseNumber));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemSelectUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[1], pos));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemTitleUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[2], pos));
	pos.y += ITEM_DISTANCE;
	m_items.push_back(std::make_unique<SystemExitUI>(DataPath::SYSTEM_SELECT_IMAGE_PATHs[3], pos));
	
	//	������
	for (auto& item : m_items)
	{
		item->Initialize();
	}
}