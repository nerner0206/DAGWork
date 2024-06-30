//--------------------------------------------------------------------------------------
// File: SystemMouseUI.h
//
// �}�E�X���x�ݒ�UI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SystemMouseUI.h"

#include "MyLib/IScene.h"
#include "GameObjects/Common/SystemWindow.h"

using namespace DirectX;

//	�ԍ��̊���W
const SimpleMath::Vector2 SystemMouseUI::NUM_POSITION = SimpleMath::Vector2(580, 240);

/// <summary>
/// �R���X�g���N�^
/// </summary>
SystemMouseUI::SystemMouseUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos, const int& num) :
	SystemUI(fileName, pos),
	m_moveNum(num)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SystemMouseUI::~SystemMouseUI()
{

}

/// <summary>
/// ������
/// </summary>
void SystemMouseUI::Initialize()
{
	//	�ԍ�UI�̐���
	for (int i = 0; i < DataPath::SYSTEM_MOUSE_NUMBER; i++)
	{
		//	UI�̐���
		std::unique_ptr<UserInterface> numUI = std::make_unique<UserInterface>();
		numUI->Create(
			DataPath::NUMBER_IMAGE_PATHs[i + 1],
			NUM_POSITION + SimpleMath::Vector2(i * NUM_DISTANCE, 0),
			SimpleMath::Vector2::One * 0.4f,
			ANCHOR::MIDDLE_CENTER);

		//	�z��֒ǉ�
		m_numUIs.push_back(std::move(numUI));
	}

	//	�I����UI�̐���
	m_frame = std::make_unique<UserInterface>();
	m_frame->Create(
		DataPath::SYSTEM_MOUSE_FRAME_IMAGE_PATH,
		m_numUIs[m_moveNum]->GetPosition(),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
void SystemMouseUI::Update(IScene* scene, SystemWindow* window)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();

	//	���E�ړ�
	if (kbTracker->pressed.Left && m_moveNum > 0)
	{
		//	�I�����̍Đ�
		GetAudioResources()->PlaySelectSE();
		//	���x�ԍ��̕ύX
		m_moveNum--;
	}	
	else if (kbTracker->pressed.Right && m_moveNum < DataPath::SYSTEM_MOUSE_NUMBER - 1)
	{
		//	�I�����̍Đ�
		GetAudioResources()->PlaySelectSE();
		//	���x�ԍ��̕ύX
		m_moveNum++;
	}

	//	�I�����̍��W�̍X�V
	m_frame->SetPosition(m_numUIs[m_moveNum]->GetPosition());
}

/// <summary>
/// �`��
/// </summary>
void SystemMouseUI::Render()
{
	//	UI�̕`��
	GetImage()->Render();

	//	�ԍ�UI�̕`��
	for (auto& numUI : m_numUIs)
	{
		numUI->Render();
	}

	//	�I���t���[���̕`��
	m_frame->Render();
}