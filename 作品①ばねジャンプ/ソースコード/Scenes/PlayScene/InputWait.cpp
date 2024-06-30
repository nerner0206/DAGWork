//--------------------------------------------------------------------------------------
// File: InputWait.cpp
//
// ���͑ҋ@��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "InputWait.h"

#include "Scenes/PlayScene/InGame.h"

#include "GameObjects/PlayScene/Camera/PlayCamera.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
InputWait::InputWait(PlayScene* scene, PlayCamera* camera) :
    IPlaySceneState(scene, camera)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputWait::~InputWait()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void InputWait::Initialize(Player* player, StageManager* stageManager)
{
    //  �X�y�[�XUI�̐���
    m_spaceUI = std::make_unique<SpaceUI>();
    m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

    //	�J�E���^�[UI�̐���
    m_counterUI = std::make_unique<CounterUI>();
    m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

    //	�J�����̍X�V
    GetPlayCamera()->Update(0.0f, player);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void InputWait::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
    SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
    //	�J�[�\�����W��߂�
    SetCursorPos(centerPos.x, centerPos.y);

	//	�L�[�{�[�h��ݒ�
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	�X�y�[�X����������Z���N�g�V�[����
	if (kbTracker->pressed.Space && GetPlayScene()->GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
        //  ���艹�̍Đ�
        GetAudioResources()->PlayDecideSE();
		//	�Z���N�g�V�[����
		GetPlayScene()->SetNextState(new InGame(GetPlayScene(), GetPlayCamera()));
		//	�������Ȃ�
		return;
	}

    //	�X�e�[�W�}�l�[�W���[�̍X�V
    stageManager->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void InputWait::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    //  �X�y�[�XUI�̕`��
    m_spaceUI->Render();
    //	�J�E���^�[�̕`��
    m_counterUI->Render(0);
}

/// <summary>
/// �I��
/// </summary>
void InputWait::Finalize()
{

}