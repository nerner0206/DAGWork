//--------------------------------------------------------------------------------------
// File: SkyDome.cpp
//
// �X�J�C�h�[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SkyDome.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDome::SkyDome() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	m_model = Model::CreateFromCMO(device, DataPath::SKYDOME_MODEL_PATH, *fx);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDome::~SkyDome()
{
	
}

/// <summary>
/// ���]
/// </summary>
/// <param name="speed">��]���x</param>
void SkyDome::RotUpdate(const float& speed)
{
	//	��]�N�H�[�^�j�I��
	SimpleMath::Quaternion q, rotate = GetRotQua();

	//	��]������
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(speed));
	rotate = q * rotate;

	//	�ݒ�
	SetRotQua(rotate);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�̎擾
	auto states = GetUserResources()->GetCommonStates();
	
	//	���[���h���W�̌v�Z
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	�T�C�Y���|����
	world *= SimpleMath::Matrix::CreateScale(GetSca());
	//	��]���|����
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	���W���|����
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	���f���̃G�t�F�N�g��ݒ�
	m_model->UpdateEffects([&](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ���C�g�̉e�����Ȃ���
				lights->SetAmbientLightColor(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷��
				basicEffect->SetEmissiveColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
		});

	//	���f���̕`��
	m_model->Draw(context, *states, world, view, proj);
}

/// <summary>
/// �I��
/// </summary>
void SkyDome::Finalize()
{
	//	���f���̃��Z�b�g
	m_model.reset();
}