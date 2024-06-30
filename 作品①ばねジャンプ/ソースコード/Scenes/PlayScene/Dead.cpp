//--------------------------------------------------------------------------------------
// File: Dead.cpp
//
// ���S��ԃN���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Dead.h"

#include "Scenes/PlayScene/InputWait.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/Camera/PlayCamera.h"

using namespace DirectX;

//	���SUI�̊g�嗦
const float Dead::DEAD_SCALE = 7.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
Dead::Dead(PlayScene* scene, PlayCamera* camera):
	IPlaySceneState(scene, camera),
	m_timer(0.0f),
	m_init(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Dead::~Dead()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void Dead::Initialize(Player* player, StageManager* stageManager)
{
	//	���S���̍Đ�
	GetAudioResources()->PlayDeadSE();

	//	���SUI�̐���
	m_deadUI = std::make_unique<UserInterface>();
	m_deadUI->Create(
		DataPath::DEAD_ICON_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, UserResources::WINDOW_HEIGHT / 2),
		SimpleMath::Vector2::Zero,
		ANCHOR::MIDDLE_CENTER);

	//	����UI�̐���
	m_blackUI = std::make_unique<UserInterface>();
	m_blackUI->Create(
		DataPath::BLACK_CIRCLE_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, UserResources::WINDOW_HEIGHT / 2),
		SimpleMath::Vector2::One,
		ANCHOR::MIDDLE_CENTER);

	//	�^�C�}�[�̏�����
	m_timer = 0.0f;
	//	�������t���O
	m_init = false;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void Dead::Update(const float& elapsedTime, Player* player, StageManager* stageManager)
{
	//	���Ԃ𑝂₷
	m_timer += elapsedTime;

	if (!m_init)
	{
		//	�g�嗦�̌v�Z
		SimpleMath::Vector2 sca = SimpleMath::Vector2::Lerp(
			SimpleMath::Vector2::Zero,
			SimpleMath::Vector2::One * DEAD_SCALE,
			m_timer);

		//	�g�嗦�̐ݒ�
		m_deadUI->SetScale(sca);

		//	��b�o�߂��Ă��Ȃ��ꍇ�A�������Ȃ�
		if (m_timer < 1.0f) return;

		//	������
		m_init = true;
		//	�^�C�}�[�̏�����
		m_timer = 0.0f;

		//	���Z�b�g
		player->Reset();
		stageManager->Reset();

		//	�J�����̍X�V
		GetPlayCamera()->Update(elapsedTime, player);

		return;
	}

	//	�g�嗦�̌v�Z(�{��)
	SimpleMath::Vector2 sca = SimpleMath::Vector2::Lerp(
		SimpleMath::Vector2::One,
		SimpleMath::Vector2::Zero,
		m_timer * 2.0f);

	//	�g�嗦�̐ݒ�
	m_blackUI->SetScale(sca);

	//	0.5�b��A���͑ҋ@��Ԃɂ���
	if(m_timer >= 0.5f) GetPlayScene()->SetNextState(new InputWait(GetPlayScene(), GetPlayCamera()));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Dead::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	1�b�ȉ�
	if (!m_init) m_deadUI->Render();
	else m_blackUI->Render();
}

/// <summary>
/// �I��
/// </summary>
void Dead::Finalize()
{
	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
	//	�J�[�\�����W��߂�
	SetCursorPos(centerPos.x, centerPos.y);
}