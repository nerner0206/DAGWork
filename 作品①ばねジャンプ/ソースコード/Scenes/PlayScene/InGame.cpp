//--------------------------------------------------------------------------------------
// File: InGame.cpp
//
// �Q�[������ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "InGame.h"

#include "Scenes/PlayScene/Dead.h"
#include "Scenes/PlayScene/Result.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

#include "GameObjects/Common/UI/CounterUI.h"

using namespace DirectX;

//	UI�̊g�嗦
const float InGame::UI_SCALE = 0.5f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
InGame::InGame(PlayScene* scene, PlayCamera* camera) :
	IPlaySceneState(scene, camera),
	m_timer(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InGame::~InGame()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void InGame::Initialize(Player* player, StageManager* stageManager)
{
	//  X�A�C�R��UI�̐���
	m_X_IconUI = std::make_unique<UserInterface>();
	m_X_IconUI->Create(
		DataPath::X_ICON_IMAGE_PATH,
		SimpleMath::Vector2(X_ICON_X, ICON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  X�{�^��UI�̐���
	m_X_ButtonUI = std::make_unique<UserInterface>();
	m_X_ButtonUI->Create(
		DataPath::X_BUTTON_IMAGE_PATH,
		SimpleMath::Vector2(X_ICON_X + BUTTON_DISTANCE, BUTTON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  C�A�C�R��UI�̐���
	m_C_IconUI = std::make_unique<UserInterface>();
	m_C_IconUI->Create(
		DataPath::C_ICON_IMAGE_PATH,
		SimpleMath::Vector2(C_ICON_X, ICON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//  C�{�^��UI�̐���
	m_C_ButtonUI = std::make_unique<UserInterface>();
	m_C_ButtonUI->Create(
		DataPath::C_BUTTON_IMAGE_PATH,
		SimpleMath::Vector2(C_ICON_X + BUTTON_DISTANCE, BUTTON_Y),
		SimpleMath::Vector2::One * UI_SCALE,
		ANCHOR::BOTTOM_LEFT);

	//	�J�E���^�[UI�̐���
	m_counterUI = std::make_unique<CounterUI>();
	m_counterUI->Initialize(PlayScene::COUNTER_POSITION);

	//	�v���C���[�̃��Z�b�g
	player->Reset();

	//	�^�C�}�[�̏�����
	m_timer = 0.0f;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void InGame::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	�v���C���Ԃ𑝂₷
	m_timer += elapsedTime;

	//	�X�e�[�W�}�l�[�W���[�̍X�V
	stageManager->Update(elapsedTime);
	//	�v���C���[�̍X�V
	player->Update(elapsedTime, stageManager);

	//	�J�����̍X�V
	GetPlayCamera()->Update(elapsedTime, player);

	//	�S�[������
	if (player->GetIsGoal())
	{
		//	���U���g��Ԃɂ���
		GetPlayScene()->SetNextState(new Result(GetPlayScene(), GetPlayCamera(), m_timer));
		return;
	}

	//	���S����
	if (player->GetIsDead())
	{
		//	���S��Ԃɂ���
		GetPlayScene()->SetNextState(new Dead(GetPlayScene(), GetPlayCamera()));
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void InGame::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	UI�̕`��
	m_C_IconUI->Render();
	m_C_ButtonUI->Render();
	m_X_IconUI->Render();
	m_X_ButtonUI->Render();

	//	�J�E���^�[�̕`��
	m_counterUI->Render((int)m_timer);
}

/// <summary>
/// �I��
/// </summary>
void InGame::Finalize()
{

}