//--------------------------------------------------------------------------------------
// File: StartBefore.cpp
//
// �J�n�O��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StartBefore.h"

#include "Scenes/PlayScene/GameStart.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

using namespace DirectX;

//	�J�������x
const float StartBefore::CAMERA_SPEED = 14.03f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
StartBefore::StartBefore(PlayScene* scene, PlayCamera* camera) :
    IPlaySceneState(scene, camera),
    m_time(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StartBefore::~StartBefore()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void StartBefore::Initialize(Player* player, StageManager* stageManager)
{
    //	�X�^�[�g���W�̎擾
    m_startPos = stageManager->GetStartPosition();
    //	�S�[�����W�̎擾
    m_goalPos= stageManager->GetGoal()->GetPos();

    //  �����̌v�Z
    float distance = (m_startPos - m_goalPos).Length();
    //  ���Ԃ̌v�Z
    m_time = distance / CAMERA_SPEED;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void StartBefore::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
    SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
    //	�J�[�\�����W��߂�
    SetCursorPos(centerPos.x, centerPos.y);

    //  �J�����̍X�V
    bool finish = GetPlayCamera()->BeforeUpdate(
        elapsedTime,
        m_startPos,
        m_goalPos,
        m_time);

    //	�X�e�[�W�}�l�[�W���[�̍X�V
    stageManager->Update(elapsedTime);

    if (finish)
    {
        //	�Z���N�g�V�[����
        GetPlayScene()->SetNextState(new GameStart(GetPlayScene(), GetPlayCamera()));
        //	�������Ȃ�
        return;
    }
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void StartBefore::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
    
}

/// <summary>
/// �I��
/// </summary>
void StartBefore::Finalize()
{

}