//--------------------------------------------------------------------------------------
// File: Result.cpp
//
// ���U���g��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Result.h"

#include "Scenes/SelectScene.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/PlayScene/Particle/ConfettiParticle.h"

#include "GameObjects/Common/UI/SpaceUI.h"
#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	����UI�̍��W
const SimpleMath::Vector2 Result::COUNTER_POSITION = SimpleMath::Vector2(640, 400);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
/// <param name="proj">�ˉe�s��</param>
Result::Result(PlayScene* scene, PlayCamera* camera, const float& resultTime) :
	IPlaySceneState(scene, camera),
	m_resultTime((int)resultTime)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Result::~Result()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void Result::Initialize(Player* player, StageManager* stageManager)
{
	//	�p�[�e�B�N���̐���
	m_confettiParticle = std::make_unique<ConfettiParticle>();
	m_confettiParticle->Initialize();

	//	�p�[�e�B�N���̔���
	m_confettiParticle->Play(stageManager->GetGoal()->GetPos());
	//	�p�[�e�B�N���̒ǉ�
	GetPlayScene()->AddParticle(m_confettiParticle.get());

	//	�N���A���̍Đ�
	GetAudioResources()->PlayClearSE();

	//  ���U���gUI�̐���
	m_resultUI = std::make_unique<UserInterface>();
	m_resultUI->Create(
		DataPath::RESULT_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT) / 2,
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//  �X�y�[�XUI�̐���
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(PlayScene::SPACE_POSITION);

	//	�J�E���^�[UI�̐���
	m_counterUI = std::make_unique<CounterUI>();
	m_counterUI->Initialize(COUNTER_POSITION);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void Result::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	�L�[�{�[�h��ݒ�
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	�X�y�[�X����������Z���N�g�V�[����
	if (kbTracker->pressed.Space)
	{
		//  ���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�Z���N�g�V�[����
		GetPlayScene()->GetSceneManager()->SetNextScene(new SelectScene());
		//	�������Ȃ�
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Result::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_resultUI->Render();

	//  �X�y�[�XUI�̕`��
	m_spaceUI->Render();
	//	�J�E���^�[�̕`��
	m_counterUI->Render(m_resultTime);
}

/// <summary>
/// �I��
/// </summary>
void Result::Finalize()
{

}