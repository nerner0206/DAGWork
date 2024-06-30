//--------------------------------------------------------------------------------------
// File: PlayScene.cpp
//
// �v���C�V�[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayScene.h"

#include "Scenes/SelectScene.h"

#include "Scenes/PlayScene/StartBefore.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/PlayScene/Camera/PlayCamera.h"
#include "GameObjects/PlayScene/Camera/DebugCamera.h"

#include "GameObjects/PlayScene/Particle/Particle.h"
#include "GameObjects/Common/BigCloud.h"

#include "imgui.h"

using namespace DirectX;

//	���C�g�̍��W
const SimpleMath::Vector3 PlayScene::LIGHT_POSITION = SimpleMath::Vector3(15.0f, 30.0f, 15.0f);
//	���C�g�̉e���͈�
const float PlayScene::LIGHT_RANGE = 100.0f;

//	�傫���_�̍��W
const SimpleMath::Vector3 PlayScene::BIG_CLOUD_POSITION = SimpleMath::Vector3(0.0f, -5.0f, 0.0f);
//	�傫���_�̊g�嗦
const float PlayScene::BIG_CLOUD_SCALE = 10.0f;

//	�X�e�[�W�ԍ�UI�̊g�嗦
const float PlayScene::STAGE_NUMBER_SCALE = 0.8f;

//	�X�y�[�XUI�̍��W
const SimpleMath::Vector2 PlayScene::SPACE_POSITION = SimpleMath::Vector2(640, 650);
//	����UI�̍��W
const SimpleMath::Vector2 PlayScene::COUNTER_POSITION = SimpleMath::Vector2(1170, 40);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="num">�X�e�[�W�ԍ�</param>
PlayScene::PlayScene(const int& stageNum):
	IScene(IScene::SceneKind::PlayScene),
	m_nowState(nullptr),
	m_nextState(nullptr),
	m_stageNum(stageNum),
	m_mode(PlaySceneMode::PlayMode)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
	
}

/// <summary>
/// ������
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void PlayScene::Initialize(const int& mouseNumber)
{
	// �ˉe�s��̍쐬
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f);
	//	�ˉe�s���ݒ肷��
	SetProjMatrix(proj);

	//	�X�e�[�W�Ǘ��N���X�̐���
	m_stageManager = std::make_unique<StageManager>();
	//	�v���C���[�̐���
	m_player = std::make_unique<Player>();

	//	�X�e�[�W�̏�����
	m_stageManager->Initialize(m_stageNum, m_player.get());

	//	�v���C���[�̏�����
	SimpleMath::Vector3 startPos = m_stageManager->GetStartPosition();

	//	�v���C�J�����̐���
	m_playCamera = std::make_unique<PlayCamera>(startPos, m_stageManager->GetGoal()->GetPos());
	//	�f�o�b�N�J�����̍쐬
	m_debugCamera = std::make_unique<DebugCamera>();

	//	�v���C���[�̏�����
	m_player->Initialize(startPos);

	//	�傫���_�N���X�̐���
	m_bigCloud = std::make_unique<BigCloud>(this);
	m_bigCloud->Initialize(BIG_CLOUD_POSITION, BIG_CLOUD_SCALE);

	//	�p�[�e�B�N���̐ݒ�
	AddParticle(m_player->GetJumpParticle());
	AddParticle(m_player->GetExplosionParticle());

	//	�v���C���[�̍��W�̎擾
	SimpleMath::Vector3 p_pos = m_player->GetPlayerSpring()->GetPos();

	// ���C�g�̈ʒu��ݒ�
	SetLightPos(p_pos + LIGHT_POSITION);
	// ���C�g�̃^�[�Q�b�g�̈ʒu��ݒ�
	SetLightTarget(p_pos);
	// ���C�g�̉e���͈͂�ݒ�
	SetLightRange(LIGHT_RANGE);

	//	�}�E�X���x�̐ݒ�
	SetMouseSpeed(mouseNumber);

	//	UI�̐���
	CreateUI();
	//	���͑O��Ԃ̐���
	SetState(new StartBefore(this, m_playCamera.get()));

	//	BGM�̍Đ�
	GetAudioResources()->PlayBGM2();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void PlayScene::Update(const float& elapsedTime)
{
	//	�L�[�{�[�h�̎擾
	auto key = Keyboard::Get().GetState();

	switch (m_mode)
	{
	//	�v���C���[�h
	case PlaySceneMode::PlayMode:			
		//	���[�h�ؑ�(ctrl+D)
		if (key.LeftControl && key.D)
		{
			//	�f�o�b�O���[�h��
			m_mode = PlaySceneMode::DebugMode;
			//	�}�E�X�J�[�\���̕\��
			ShowCursor(true);

			//	�����I��
			return;
		}

		//	���̏�Ԃ����݂���
		if (m_nextState)
		{
			//	���̏�Ԃ̐ݒ�
			SetState(m_nextState);
			//	���̏�Ԃ̍폜
			m_nextState = nullptr;
		}

		//	��Ԃ̍X�V
		if (m_nowState) m_nowState->Update(elapsedTime, m_player.get(), m_stageManager.get());

		//	�J�������W�̎擾
		SetCameraPos(m_playCamera->GetPos());
		//	�J�����ڕW���W�̎擾
		SetCameraTarget(m_playCamera->GetTargetPosition());
		break;

	//	�f�o�b�O���[�h
	case PlaySceneMode::DebugMode:			
		//	���[�h�ؑ�(ctrl+S)
		if (key.LeftControl && key.S)
		{
			//	�v���C���[�h��
			m_mode = PlaySceneMode::PlayMode;
			//	�}�E�X�J�[�\���̍폜
			ShowCursor(false);
			//	�f�[�^�̕ۑ�
			SaveData();

			//	���Z�b�g
			m_player->Reset();
			m_stageManager->Reset();
			return;
		}

		//	�f�o�b�N�J�����̍X�V����
		m_debugCamera->Update();

		//	�J�������W�̎擾
		SetCameraPos(m_debugCamera->GetPos());
		//	�J�����ڕW���W�̎擾
		SetCameraTarget(m_debugCamera->GetTargetPosition());
		break;
	}

	//	�p�[�e�B�N���̍X�V
	for (auto& particle : m_particles)
	{
		if (particle->GetActive()) particle->Update(elapsedTime);
	}

	//	�v���C���[�̍��W�̎擾
	SimpleMath::Vector3 p_pos = m_player->GetPlayerSpring()->GetPos();
	// ���C�g�̈ʒu��ݒ�
	SetLightPos(p_pos + LIGHT_POSITION);
	// ���C�g�̃^�[�Q�b�g�̈ʒu��ݒ�
	SetLightTarget(p_pos);
}

/// <summary>
/// �`��
/// </summary>
void PlayScene::Render()
{
	//	�v���C�J��������r���[�s��̎擾
	if(m_mode == PlaySceneMode::PlayMode) SetViewMatrix(m_playCamera->GetViewMatrix());
	//	�f�o�b�O�J��������r���[�s��̎擾
	else SetViewMatrix(m_debugCamera->GetViewMatrix());

	//	�X�J�C�h�[���̕`��
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());
	//	�傫���_�̕`��
	m_bigCloud->Render(GetViewMatrix(), GetProjMatrix());

	//	�X�e�[�W�Ǘ��N���X�̕`��
	m_stageManager->Render(GetViewMatrix(), GetProjMatrix());
	//	�v���C���[�̕`��
	m_player->Render(GetViewMatrix(), GetProjMatrix());

	//	�p�[�e�B�N���̕`��
	for (auto& particle : m_particles)
	{
		if (particle->GetActive()) particle->Render(GetViewMatrix(), GetProjMatrix());
	}

	//	UI�̕`��
	m_stageUI->Render();
	m_stageNumUI->Render();

	switch (m_mode)
	{
	//	�v���C���[�h
	case PlaySceneMode::PlayMode:
		//	��Ԃ̕`��
		if (m_nowState) m_nowState->Render(GetViewMatrix(), GetProjMatrix());
		break;

	//	�f�o�b�O���[�h
	case PlaySceneMode::DebugMode:
		//	�v���C�J�����̃f�o�b�O�`��
		m_playCamera->DebugRender(GetViewMatrix(), GetProjMatrix());
		//	�v���C���[�̃f�o�b�O�`��
		m_player->DebugRender();
		//	�X�e�[�W�Ǘ��N���X�̃f�o�b�O�`��
		m_stageManager->DebugRender();
		break;
	}
}

/// <summary>
/// �e�`��
/// </summary>
void PlayScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view, proj;

	//----- �V���h�E�}�b�v�̍쐬 -----//
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	�v���C���[�̉e���V���h�E�}�b�v�֕`��
			m_player->ShadowRender(view, proj);
			//	�X�e�[�W�I�u�W�F�N�g�ւ̉e�̕`��
			m_stageManager->ShadowRender(view, proj);
		}
	);
}

/// <summary>
/// �I��
/// </summary>
void PlayScene::Finalize()
{
	//	BGM�̒�~
	GetAudioResources()->StopBGM2();

	//	���݂̃v���C�V�[����Ԃ��폜
	DeletePlaySceneState();

	m_player->Finalize();
	m_stageManager->Finalize();
	m_bigCloud->Finalize();
}

/// <summary>
/// �v���C�V�[����Ԃ̐ݒ�
/// </summary>
/// <param name="state">�v���C�V�[����ԃN���X�̃|�C���^</param>
void PlayScene::SetState(IPlaySceneState* state)
{
	// �V�[�����폜
	DeletePlaySceneState();

	// �V�[���𐶐�
	m_nowState = state;

	// �V�[���̏���������
	m_nowState->Initialize(m_player.get(), m_stageManager.get());
}

/// <summary>
/// ���̃v���C�V�[����Ԃ̐ݒ�
/// </summary>
/// <param name="state">�v���C�V�[����ԃN���X�̃|�C���^</param>
void PlayScene::SetNextState(IPlaySceneState* state)
{
	if (m_nextState) return;

	// �V�[���𐶐�
	m_nextState = state;
}
/// <summary>
/// �v���C�V�[����Ԃ̍폜
/// </summary>
void PlayScene::DeletePlaySceneState()
{
	//	���݂̃V�[����������Ώ������Ȃ�
	if (!m_nowState) return;

	//	�V�[���̏I������
	m_nowState->Finalize();
	//	�V�[���̍폜
	delete m_nowState;
	//	nullptr���i�[
	m_nowState = nullptr;
}

/// <summary>
/// UI�̐���
/// </summary>
void PlayScene::CreateUI()
{
	//	�X�e�[�WUI�̐���
	m_stageUI = std::make_unique<UserInterface>();
	m_stageUI->Create(
		DataPath::STAGE_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH - STAGE_DISTANCE, UserResources::WINDOW_HEIGHT),
		SimpleMath::Vector2::One,
		ANCHOR::BOTTOM_RIGHT);

	//	�X�e�[�W�ԍ�UI�̐���
	m_stageNumUI = std::make_unique<UserInterface>();
	m_stageNumUI->Create(
		DataPath::NUMBER_IMAGE_PATHs[m_stageNum + 1],
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT),
		SimpleMath::Vector2::One * STAGE_NUMBER_SCALE,
		ANCHOR::BOTTOM_RIGHT);
}

/// <summary>
/// �}�E�X���x�̐ݒ�
/// </summary>
/// <param name="num">�}�E�X���x</param>
void PlayScene::SetMouseSpeed(const int& mouseNumber)
{
	//	�}�E�X���x�̌v�Z
	float sensitivity = (float)(mouseNumber + 1) / (float)DataPath::SYSTEM_MOUSE_NUMBER;

	//	�}�E�X���x�̐ݒ�
	m_player->SetMouseSensitivity(sensitivity);
}

/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
void PlayScene::SaveData()
{
	//	�v���C�J�����̕ۑ�
	m_playCamera->SaveData();
	//	�v���C���[�̕ۑ�
	m_player->SaveData();
	//	�X�e�[�W�̕ۑ�
	m_stageManager->SaveData(m_stageNum);
}