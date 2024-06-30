//--------------------------------------------------------------------------------------
// File: Cloud.cpp
//
// �_�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Cloud.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Cloud::Cloud() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cloud::~Cloud()
{
	
}

/// <summary>
/// ������
/// </summary>
/// <param name="filePath">�_���f���̃t�@�C���p�X</param>
void Cloud::Initialize(const wchar_t* filePath)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	m_model = Model::CreateFromCMO(device, filePath, *fx);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Cloud::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	���f���̕`��
	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, false);
		});
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Cloud::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	�T�C�Y�ύX
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	��]��������
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	���W���ړ�������
	SimpleMath::Matrix pos = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	�s����v�Z
	m_world = sca * rot * pos;

	//	���f���̕`��
	m_model->Draw(context, *states, m_world, view, proj, false, [&]() 
		{
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// �I��
/// </summary>
void Cloud::Finalize()
{
	//	���f���̃��Z�b�g
	m_model.reset();
}