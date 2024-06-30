//--------------------------------------------------------------------------------------
// File: SpringPart.cpp
//
// �v���C���[�΂˂̕��i�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringPart.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SpringPart::SpringPart() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpringPart::~SpringPart()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="fileName">���f���̃t�@�C���p�X</param>
void SpringPart::Initialize(const wchar_t* fileName)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̐���
	m_model = Model::CreateFromCMO(device, fileName, *fx);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
void SpringPart::Update(
	const float& elapsedTime,
	const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate)
{

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void SpringPart::Render(
	const SimpleMath::Matrix& world,
	const SimpleMath::Matrix& view,
	const SimpleMath::Matrix& proj)
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();
	auto shadowMap = GetUserResources()->GetShadowMap();

	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, true);
		}
	);
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void SpringPart::ShadowRender(
	const SimpleMath::Matrix& world,
	const SimpleMath::Matrix& view,
	const SimpleMath::Matrix& proj)
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	�ړ�������
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());
	//	��]���|����
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());

	m_world = rot * world  * trans;

	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			// �V���h�E�}�b�v�֕`��
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// �I��
/// </summary>
void SpringPart::Finalize()
{
	m_model.reset();
}