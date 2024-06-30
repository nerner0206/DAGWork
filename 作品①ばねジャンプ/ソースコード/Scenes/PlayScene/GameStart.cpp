//--------------------------------------------------------------------------------------
// File: GameStart.cpp
//
// �Q�[���J�n��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "GameStart.h"

#include "Scenes/PlayScene/InGame.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	���[��UI�̍��W
const SimpleMath::Vector2 GameStart::RULU_POSITION = SimpleMath::Vector2(30, 30);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
GameStart::GameStart(PlayScene* scene, PlayCamera* camera):
    IPlaySceneState(scene, camera)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameStart::~GameStart()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void GameStart::Initialize(Player* player, StageManager* stageManager)
{
    //  ���[��UI�̐���
    m_ruluUI = std::make_unique<UserInterface>();
    m_ruluUI->Create(
        DataPath::RULU_IMAGE_PATH,
        RULU_POSITION,
        SimpleMath::Vector2::One,
        ANCHOR::TOP_LEFT);

    //  �X�y�[�XUI�̐���
    m_spaceUI = std::make_unique<SpaceUI>();
    m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

    //	�J�E���^�[UI�̐���
    m_counterUI = std::make_unique<CounterUI>();
    m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

    //	�v���C���[�̃��Z�b�g
    player->Reset();

    //	�J�����̍X�V
    GetPlayCamera()->Update(0.0f, player);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void GameStart::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	�L�[�{�[�h�̎擾
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	�X�y�[�X����������Z���N�g�V�[����
	if (kbTracker->pressed.Space && GetPlayScene()->GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
        //  ���艹�̍Đ�
        GetAudioResources()->PlayDecideSE();
		//	�Q�[������
		GetPlayScene()->SetNextState(new InGame(GetPlayScene(), GetPlayCamera()));
		//	�������Ȃ�
		return;
	}

    //	�X�e�[�W�}�l�[�W���[�̍X�V
    stageManager->Update(elapsedTime);

    //  �v���C���[�΂˃N���X�ɃL���X�g
    PlayerSpring* spring = dynamic_cast<PlayerSpring*>(player->GetPlayerSpring());
    //  ��]�̍X�V
    spring->TestUpdate(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void GameStart::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    //  ���[��UI�̕`��
    m_ruluUI->Render();

    //  �X�y�[�XUI�̕`��
    m_spaceUI->Render();
    //	�J�E���^�[�̕`��
    m_counterUI->Render(0);
}

/// <summary>
/// �I��
/// </summary>
void GameStart::Finalize()
{
    
}