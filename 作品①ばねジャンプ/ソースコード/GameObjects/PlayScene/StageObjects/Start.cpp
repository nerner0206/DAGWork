//--------------------------------------------------------------------------------------
// File: Start.cpp
//
// �X�^�[�g�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Start.h"

#include "MyLib/UserResources.h"
#include "Game/DataPath.h"

using namespace DirectX;

//	�J�n���W
const SimpleMath::Vector3 Start::START_POSITION = SimpleMath::Vector3(0.0f, 2.0f, 0.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
Start::Start() :
	Object(START_POSITION, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Start::~Start()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">���W</param>
void Start::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̐���
	m_model = Model::CreateFromCMO(device, DataPath::STAGE_START_MODEL_PATH, *fx);

	//	���[���h�s��̌v�Z
	m_world = SimpleMath::Matrix::CreateTranslation(GetPos());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Start::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();

	//	���f���̕`��
	m_model->Draw(context, *states, m_world, view, proj);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void Start::DebugRender()
{

}

/// <summary>
/// �I��
/// </summary>
void Start::Finalize()
{
	//	���f���̃��Z�b�g
	m_model.reset();
}
