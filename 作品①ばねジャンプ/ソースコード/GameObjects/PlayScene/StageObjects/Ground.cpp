//--------------------------------------------------------------------------------------
// File: Ground.cpp
//
// ����N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Ground.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
Ground::Ground(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	IStageObject(StageObjType::Cloud, pos, rot, sca),
	m_isShake(false),
	m_t(0.0f)
{
	//	�h��̊g�嗦
	m_defSca = sca;
	m_targetSca = sca;
	m_targetSca.x *= 1.05f;
	m_targetSca.z *= 1.05f;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Ground::~Ground()
{

}

/// <summary>
/// ������
/// </summary>
void Ground::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_CLOUD_MODEL_PATH, *fx);
	//	���f����ݒ肷��
	SetModel(std::move(model));

	//	�����蔻��𐶐�
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̏����X�V����
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	���̓����蔻���ݒ肷��
	SetCollisionObject(std::move(boxCollider));
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void Ground::Update(const float& elapsedTime)
{
	//	�_�̗h��
	Shaking(elapsedTime);

	//	�����蔻��̍X�V
	GetCollisionObject()->ColliderUpdate(GetPos(), GetRotQua(), GetSca());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Ground::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	���f���̕`��
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, false);
		});
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Ground::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	�g�嗦
	SimpleMath::Matrix p_sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	��]
	SimpleMath::Matrix p_rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	�ړ�
	SimpleMath::Matrix p_trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	���[���h�s��̌v�Z
	SimpleMath::Matrix world = p_sca * p_rot * p_trans;
	//	���[���h�s���ݒ肷��
	SetWorldMatrix(world);

	//	���f���̕`��
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void Ground::DebugRender()
{
	//	�X�e�[�W�I�u�W�F�N�g�̎��
	ImGui::Text("Cloud");
	//	���ʃf�o�b�O�`��
	CommonDebugRender();
}

/// <summary>
/// �I��
/// </summary>
void Ground::Finalize()
{

}

/// <summary>
/// ���Z�b�g
/// </summary>
void Ground::Reset()
{
	SetIsHitActive(true);
}

/// <summary>
///	�h���
/// </summary>
void Ground::Shaking(const float& elapsedTime)
{
	//	�h��Ȃ�
	if (!m_isShake) return;

	//	��ԗ��̑���
	m_t += elapsedTime;
	//	�g�嗦�̐ݒ�
	SimpleMath::Vector3 sca = m_defSca;
	
	if (m_t > 0.5f)
	{
		//	3�{��
		m_t += elapsedTime * 2.0f;
		//	�g�嗦�̕ύX
		sca = SimpleMath::Vector3::Lerp(m_targetSca, m_defSca, (m_t - 0.5f) * 2.0f);

		if (m_t > 1.0f)
		{
			m_t = 0.0f;
			m_isShake = false;
		}
	}
	else
	{
		//	�g�嗦�̕ύX
		sca = SimpleMath::Vector3::Lerp(m_defSca, m_targetSca, m_t * 2.0f);
	}

	//	�g�嗦�̐ݒ�
	SetSca(sca);
}