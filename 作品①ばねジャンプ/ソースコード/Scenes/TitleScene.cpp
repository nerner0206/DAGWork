//--------------------------------------------------------------------------------------
// File: TitleScene.cpp
//
// �^�C�g���V�[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TitleScene.h"

#include "Scenes/SelectScene.h"

#include "GameObjects/TitleScene/TitleTextModels.h"
#include "GameObjects/Common/Cloud.h"
#include "GameObjects/Common/BigCloud.h"

#include "GameObjects/Common/UI/SpaceUI.h"

#include "MyLib/AudioResources.h"

using namespace DirectX;

//	���C�g�̍��W
const SimpleMath::Vector3 TitleScene::LIGHT_POSITION = SimpleMath::Vector3(0.0f, 30.0f, 15.0f);
//	���C�g�̉e���͈�
const float TitleScene::LIGHT_RANGE = 100.0f;

//	�J�����̍��W
const SimpleMath::Vector3 TitleScene::CAMERA_POSITION = SimpleMath::Vector3(-2.0f, 2.0f, 5.0f);

//	�_�̍��W
const SimpleMath::Vector3 TitleScene::CLOUD_POSITION = SimpleMath::Vector3(0.0f, -0.15f, -1.0f);

//	�傫���_�̍��W
const SimpleMath::Vector3 TitleScene::BIG_CLOUD_POSITION = SimpleMath::Vector3(0.0f, -5.0f, 0.0f);
//	�傫���_�̊g�嗦
const float TitleScene::BIG_CLOUD_SCALE = 10.0f;

//	�X�J�C�h�[���̉�]���x
const float TitleScene::ROT_SPEED = 0.02f;

//	�X�y�[�XUI�̍��W
const SimpleMath::Vector2 TitleScene::SPACE_UI_POSITION = SimpleMath::Vector2(1030, 600);

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene() :
	IScene(IScene::SceneKind::TitleScene)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene() 
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
void TitleScene::Initialize(const int& mouseNumber)
{
	// �ˉe�s��̍쐬
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f
	);
	//	�ˉe�s��̐ݒ�
	SetProjMatrix(proj);

	// ���C�g�̍��W�̐ݒ�
	SetLightPos(LIGHT_POSITION);
	// ���C�g�̖ڕW���W�̐ݒ�
	SetLightTarget(SimpleMath::Vector3::Zero);
	// ���C�g�̉e���͈͂̐ݒ�
	SetLightRange(LIGHT_RANGE);

	//	�J�����̍��W�̐ݒ�
	SetCameraPos(CAMERA_POSITION);
	//	�J�����̖ڕW���W�̐ݒ�
	SetCameraTarget(SimpleMath::Vector3::Zero);

	//	�r���[�s��̍쐬
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		GetCameraPos(),
		GetCameraTarget(),
		SimpleMath::Vector3::Up);
	//	�r���[�s��̐ݒ�
	SetViewMatrix(view);

	//	�_�N���X�̐���
	m_cloud = std::make_unique<Cloud>();
	m_cloud->Initialize(DataPath::TITLE_CLOUD_MODEL_PATH);
	//	�_�̍��W�̐ݒ�
	m_cloud->SetPos(CLOUD_POSITION);

	//	�^�C�g���������f���̐���
	m_titleTextModel = std::make_unique<TitleTextModels>();
	m_titleTextModel->Initialize();

	//	�傫���_�N���X�̐���
	m_bigCloud = std::make_unique<BigCloud>(this);
	m_bigCloud->Initialize(BIG_CLOUD_POSITION, BIG_CLOUD_SCALE);

	//	UI�̍쐬
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(SPACE_UI_POSITION);

	//	BGM�̍Đ�
	GetAudioResources()->PlayBGM1();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void TitleScene::Update(const float& elapsedTime)
{
	//	�X�J�C�h�[���̉�]
	GetSkyDome()->RotUpdate(ROT_SPEED);

	//	�L�[�{�[�h��ݒ�
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	���f���̍X�V
	m_titleTextModel->Update(elapsedTime);

	//	�X�y�[�X����������Z���N�g�V�[����
	if (kbTracker->pressed.Space && GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
		//	���艹�̍Đ�
		GetAudioResources()->PlayDecideSE();
		//	�Z���N�g�V�[����
		GetSceneManager()->SetNextScene(new SelectScene());
		//	�������Ȃ�
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Render()
{
	//	�X�J�C�h�[���̕`��
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());
	//	�傫���_�̕`��
	m_bigCloud->Render(GetViewMatrix(), GetProjMatrix());

	//	�_�̕`��
	m_cloud->Render(GetViewMatrix(), GetProjMatrix());
	//	�e�L�X�g���f���̕`��
	m_titleTextModel->Render(GetViewMatrix(), GetProjMatrix());

	//	UI�̕`��
	m_spaceUI->Render();
}

/// <summary>
/// �e�`��
/// </summary>
void TitleScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix proj = SimpleMath::Matrix::Identity;

	//	�V���h�E�}�b�v�̍쐬
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	�e�L�X�g���f���̕`��
			m_titleTextModel->ShadowRender(view, proj);
			//	�_�̕`��
			m_cloud->ShadowRender(view, proj);
		}
	);
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	//	BGM�̒�~
	GetAudioResources()->StopBGM1();

	m_titleTextModel->Finalize();
	m_cloud->Finalize();
	m_bigCloud->Finalize();
}