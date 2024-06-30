//--------------------------------------------------------------------------------------
// File: SelectScene.cpp
//
// �Z���N�g�V�[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SelectScene.h"

#include "Scenes/TitleScene.h"
#include "Scenes/PlayScene.h"

#include "GameObjects/Common/TextModel.h"
#include "GameObjects/Common/Cloud.h"

#include "GameObjects/Common/UI/SpaceUI.h"

#include "MyLib/AudioResources.h"

using namespace DirectX;

//	�X�J�C�h�[���̉�]���x
const float SelectScene::SKYDOME_ROT_SPEED = 0.02f;

//	���f���Ԃ̋���
const float SelectScene::MODEL_DISTANCE = 5.0f;
//	���f���̍��WY�EZ
const float SelectScene::MODEL_POS_Y = -1.0f;
const float SelectScene::MODEL_POS_Z = -10.0f;
//	�e�L�X�g���f���̍��WY
const float SelectScene::TEXT_MODEL_POS_Y = 0.3f;
//	���f���̏k���{��
const float SelectScene::MODEL_MIN_SCALE = 0.5f;

//	�J�����̖ڕW���W
const SimpleMath::Vector3 SelectScene::CAMERA_TARGET_POSITION = SimpleMath::Vector3(0.0f, 0.0f, -10.0f);
//	���C�g�̉e���͈�
const float SelectScene::LIGHT_RANGE = 20.0f;

//	�^�C�g���摜�̊g�嗦
const float SelectScene::TITLE_IMAGE_SCALE = 0.8f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectScene::SelectScene():
	IScene(IScene::SceneKind::SelectScene),
	m_stageNum(0),
	m_stageBeforeNum(0),
	isChange(false),
	m_timer(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectScene::~SelectScene()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void SelectScene::Initialize(const int& mouseNumber)
{
	// �ˉe�s����쐬
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f
	);
	//	�ˉe�s���ݒ藯��
	SetProjMatrix(proj);

	//	X���W�̊J�n�ʒu
	float startPosX = -DataPath::STAGE_NUMBER / 2 * MODEL_DISTANCE;

	//	�J�����̍��W��ݒ肷��
	SetCameraPos(SimpleMath::Vector3(startPosX, 0.0f, 0.0f));
	//	�J�����̖ڕW���W��ݒ肷��
	SetCameraTarget(GetCameraPos() + CAMERA_TARGET_POSITION);

	// ���C�g�̈ʒu��ݒ�
	SetLightPos(GetCameraPos());
	// ���C�g�̖ڕW���W��ݒ�
	SetLightTarget(GetCameraTarget());
	// ���C�g�̉e���͈͂�ݒ�
	SetLightRange(LIGHT_RANGE);

	//	�_�ƃe�L�X�g
	for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
	{
		//	���W�̎Z�o
		SimpleMath::Vector3 pos = SimpleMath::Vector3(startPosX, MODEL_POS_Y, MODEL_POS_Z);
		pos.x += (i * MODEL_DISTANCE);

		//	�쐬
		std::unique_ptr<Cloud> cloud = std::make_unique<Cloud>();
		//	������
		cloud->Initialize(DataPath::SELECT_CLOUD_MODEL_PATH);
		//	���W��ݒ�
		cloud->SetPos(pos);

		//	�T�C�Y��ύX
		if (i == m_stageNum) cloud->SetSca(SimpleMath::Vector3::One);
		else cloud->SetSca(SimpleMath::Vector3::One * MODEL_MIN_SCALE);

		//	�z��ɓn��
		m_clouds.push_back(std::move(cloud));

		//	�e�L�X�g���f���̍쐬
		std::unique_ptr<TextModel> text = std::make_unique<TextModel>();
		//	������
		text->Initialize(DataPath::SELECT_TEXT_MODEL_PATHs[i]);
		//	���W��ݒ�
		text->SetPos(pos + SimpleMath::Vector3::UnitY * TEXT_MODEL_POS_Y);

		//	�g�嗦�̕ύX
		if (i == m_stageNum) text->SetSca(SimpleMath::Vector3::One); 
		else text->SetSca(SimpleMath::Vector3::One * MODEL_MIN_SCALE);

		//	�z��ɓn��
		m_textModels.push_back(std::move(text));
	}

	//	�Z���N�g�^�C�g��UI�̐���
	m_selectTitleUI = std::make_unique<UserInterface>();
	m_selectTitleUI->Create(
		DataPath::SELECT_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::TOP_LEFT);

	//	�X�y�[�XUI�̐���
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, SPACE_UI_HEIGHT));

	//	�E���̐���
	m_rightArrowUI = std::make_unique<UserInterface>();
	m_rightArrowUI->Create(
		DataPath::RIGHT_ARROW_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2 + ARROW_IMAGE_DISTANCE, SPACE_UI_HEIGHT),
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::MIDDLE_CENTER);

	//	�����̐���
	m_leftArrowUI = std::make_unique<UserInterface>();
	m_leftArrowUI->Create(
		DataPath::LEFT_ARROW_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2 - ARROW_IMAGE_DISTANCE, SPACE_UI_HEIGHT),
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::MIDDLE_CENTER);

	//	BGM�̍Đ�
	GetAudioResources()->PlayBGM1();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void SelectScene::Update(const float& elapsedTime)
{
	//	�X�J�C�h�[���̉�]
	GetSkyDome()->RotUpdate(SKYDOME_ROT_SPEED);

	//	�ύX��
	if (isChange)
	{
		//	���Ԃ𑝉�����
		m_timer += elapsedTime;

		//	1�b��o��
		if (m_timer >= 1.0f)
		{
			//	�ړ��̏I��
			isChange = false;
			//	1.0�ɐ�����
			m_timer = 1.0f;
		}

		//	�g�嗦�����X�ɑ傫������
		SimpleMath::Vector3 sca = SimpleMath::Vector3::Lerp(
			SimpleMath::Vector3::One * MODEL_MIN_SCALE,
			SimpleMath::Vector3::One,
			m_timer);

		//	�g�嗦�̐ݒ�
		m_clouds[m_stageNum]->SetSca(sca);
		m_textModels[m_stageNum]->SetSca(sca);

		sca = SimpleMath::Vector3::Lerp(
			SimpleMath::Vector3::One,
			SimpleMath::Vector3::One * MODEL_MIN_SCALE,
			m_timer);

		//	�g�嗦�̐ݒ�
		m_clouds[m_stageBeforeNum]->SetSca(sca);
		m_textModels[m_stageBeforeNum]->SetSca(sca);

		//	�ڕW���W�����X�ɋ߂Â�
		SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(
			m_cameraNowPos,
			m_cameraNextPos,
			m_timer);

		//	�J�����̍��W��ݒ�
		SetCameraPos(pos);
		//	�J�����̖ڕW���W��ݒ肷��
		SetCameraTarget(pos + CAMERA_TARGET_POSITION);

		// ���C�g�̈ʒu��ݒ�
		SetLightPos(GetCameraPos());
		// ���C�g�̖ڕW���W��ݒ�
		SetLightTarget(GetCameraTarget());

		return;
	}

	//	�L�[�{�[�h�g���b�J�[���擾
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	�X�y�[�X����������v���C�V�[����
	if (kbTracker->pressed.Space && GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
		//	���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�Z���N�g�V�[����
		GetSceneManager()->SetNextScene(new PlayScene(m_stageNum));
		//	�������Ȃ�
		return;
	}

	//	���̃X�e�[�W
	if (kbTracker->pressed.Right &&
		GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main &&
		m_stageNum != DataPath::STAGE_NUMBER - 1)
	{
		//	�ȑO�̔ԍ���ۑ�
		m_stageBeforeNum = m_stageNum;
		//	���̔ԍ���
		m_stageNum++;

		//	�ύX
		ChangeStage();
	}
	//	�O�̃X�e�[�W
	else if (kbTracker->pressed.Left &&
		GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main &&
		m_stageNum != 0)
	{
		//	�ȑO�̔ԍ���ۑ�
		m_stageBeforeNum = m_stageNum;
		//	�O�̔ԍ���
		m_stageNum--;

		//	�ύX
		ChangeStage();
	}
}

/// <summary>
/// �`��
/// </summary>
void SelectScene::Render()
{
	//	�r���[�s��̍쐬
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		GetCameraPos(),
		GetCameraTarget(),
		SimpleMath::Vector3::Up
	);
	//	�r���[�s��̐ݒ�
	SetViewMatrix(view);

	//	�X�J�C�h�[��
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());

	//	�_�ƃe�L�X�g
	for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
	{
		//	���f���̕`��
		m_textModels[i]->Render(GetViewMatrix(), GetProjMatrix());
		//	�_�̕`��
		m_clouds[i]->Render(GetViewMatrix(), GetProjMatrix());
	}

	//	�Z���N�g�^�C�g��UI�̕`��
	m_selectTitleUI->Render();

	//	�X�y�[�XUI�̕`��
	m_spaceUI->Render();

	//	�E���̕`��
	if (m_stageNum != DataPath::STAGE_NUMBER - 1) m_rightArrowUI->Render();
	//	�����̕`��
	if (m_stageNum != 0) m_leftArrowUI->Render();
}

/// <summary>
/// �e�`��
/// </summary>
void SelectScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix proj = SimpleMath::Matrix::Identity;

	//----- �V���h�E�}�b�v�̍쐬 -----//
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	�_�ƃe�L�X�g
			for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
			{
				//	���f���̕`��
				m_textModels[i]->ShadowRender(GetViewMatrix(), GetProjMatrix());
				//	�_�̕`��
				m_clouds[i]->ShadowRender(GetViewMatrix(), GetProjMatrix());
			}
		}
	);
}

/// <summary>
/// �I��
/// </summary>
void SelectScene::Finalize()
{
	//	BGM�̒�~
	GetAudioResources()->StopBGM1();

	//	�_�̕`��
	for (auto& cloud : m_clouds)
	{
		cloud->Finalize();
	}
	//	�_�̕`��
	for (auto& text : m_textModels)
	{
		text->Finalize();
	}
}

/// <summary>
/// �X�e�[�W�ύX
/// </summary>
void SelectScene::ChangeStage()
{
	//	�I�����̍Đ�
	GetAudioResources()->PlaySelectSE();

	//	���݂̍��W
	m_cameraNowPos = GetCameraPos();
	//	���̍��W
	m_cameraNextPos = SimpleMath::Vector3(
		m_clouds[m_stageNum]->GetPos().x, 0.0f, 0.0f);

	//	�ύX��
	isChange = true;
	//	���Ԃ����Z�b�g
	m_timer = 0.0f;
}