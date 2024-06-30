//--------------------------------------------------------------------------------------
// File: SceneManager.cpp
//
// �V�[���Ǘ��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SceneManager.h"

#include "GameObjects/Common/SystemWindow.h"
#include "GameObjects/Common/FadeCloud.h"

#include "MyLib/IScene.h"

using namespace DirectX;

//	�f�[�^�A�N�Z�X�p�̕�����
const std::string SceneManager::DATA_STR = "Sensitivity";

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager() :
	m_nowScene(nullptr),
	m_nextScene(nullptr),
	m_sceneState(SceneState::FadeIn)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	//	�ݒ��ʂ̏I��
	m_system->Finalize();
	//	�V�[���̍폜
	DeleteScene();
}

/// <summary>
/// ������
/// </summary>
void SceneManager::Initialize()
{
	//	�X�e�[�Wjson�̓ǂݍ���
	m_systemData = JsonManager::LoadFile(DataPath::SYSTEM_DATA_PATH);

	//	�ݒ��ʂ̐���
	m_system = std::make_unique<SystemWindow>();
	m_system->Initialize(m_systemData[DATA_STR]);

	//	�t�F�C�h�p�̉_�̐���
	m_fade = std::make_unique<FadeCloud>();
	m_fade->Initialize();

	//	�t�F�C�h�C���ݒ�
	m_fade->FadeInStart();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void SceneManager::Update(const float& elapsedTime)
{
	//	�ݒ��ʂ̍X�V
	if (m_system->GetIsSystemOpen()) 
	{
		m_system->Update(m_nowScene);
		return;
	}

	//	�t�F�C�h�C������
	if (m_sceneState == SceneState::FadeIn)
	{
		//	�t�F�C�h�C���I������
		if (m_fade->FadeInUpdate(elapsedTime)) 
			m_sceneState = SceneState::Main;
	}
	//	�t�F�C�h�A�E�g����
	else if (m_sceneState == SceneState::FadeOut)
	{
		//	�t�F�C�h�A�E�g�I������
		if (m_fade->FadeOutUpdate(elapsedTime))
		{
			//	�V�[���̐ݒ�
			SetScene(m_nextScene);
			//	���̃V�[��������
			m_nextScene = nullptr;

			//	�t�F�C�h�C����
			m_sceneState = SceneState::FadeIn;
		}
		return;
	}

	//	�Q�[���̍X�V
	MainUpdate(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
void SceneManager::Render()
{
	//	�V�[���̕`��
	if (m_nowScene) m_nowScene->Render();

	//	�ݒ��ʂ̕`��
	if (m_system->GetIsSystemOpen()) m_system->Render();

	//	UI�̕`��
	if(m_sceneState != SceneState::Main) m_fade->Render();
}

/// <summary>
/// �e�`��
/// </summary>
void SceneManager::ShadowRender()
{
	//	�V�[���̕`��
	if (m_nowScene) m_nowScene->ShadowRender();
}

/// <summary>
/// �V�[����ݒ�i�����j
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
void SceneManager::SetScene(IScene* scene)
{
	// �V�[�����폜
	DeleteScene();

	// �V�[���𐶐�
	m_nowScene = scene;
	// �V�[���ɃV�[���}�l�[�W���[�ւ̃|�C���^��ݒ�
	m_nowScene->SetSceneManager(this);
	// �V�[���̏���������
	m_nowScene->Initialize(m_systemData[DATA_STR]);
}

/// <summary>
/// ���̃V�[����ݒ�i�V�[���ړ��j
/// </summary>
/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
void SceneManager::SetNextScene(IScene* scene)
{
	if (m_nextScene) return;

	// �V�[���𐶐�
	m_nextScene = scene;
}

/// <summary>
/// �V�[���̍폜
/// </summary>
void SceneManager::DeleteScene()
{
	//	���݂̃V�[����������Ώ������Ȃ�
	if (!m_nowScene) return;

	//	�V�[���̏I������
	m_nowScene->Finalize();
	//	�V�[���̍폜
	delete m_nowScene;
	//	nullptr���i�[
	m_nowScene = nullptr;
}

/// <summary>
/// �C���Q�[���̏���
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void SceneManager::MainUpdate(const float& elapsedTime)
{
	//	�V�[���̐؂�ւ�
	if (m_nextScene && m_sceneState == SceneState::Main)
	{
		//	�t�F�C�h�A�E�g
		m_sceneState = SceneState::FadeOut;
		m_fade->FadeOutStart();

		return;
	}

	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	ESC�L�[�������ꂽ��ݒ��ʂ̊J�n
	if (kbTracker->pressed.Escape && m_sceneState == SceneState::Main)
	{
		//	�ݒ��ʂ��J��
		m_system->OnWindow(m_nowScene);
		return;
	}

	//	�V�[���̍X�V
	if (m_nowScene) m_nowScene->Update(elapsedTime);
}

/// <summary>
/// �V�X�e���ݒ�̕ۑ�
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void SceneManager::SaveSystem(const int& mouseNumber)
{
	//	�}�E�X���x�ԍ��̍X�V
	m_systemData[DATA_STR] = mouseNumber;

	//	�f�[�^�̕ۑ�
	JsonManager::SaveFile(DataPath::SYSTEM_DATA_PATH, m_systemData);
}