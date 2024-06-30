//--------------------------------------------------------------------------------------
// File: Balloon.cpp
//
// ���D�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Balloon.h"

#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
Balloon::Balloon(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	IStageObject(StageObjType::Balloon, pos, rot, sca)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Balloon::~Balloon()
{
	
}

/// <summary>
/// ������
/// </summary>
void Balloon::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_BALLOON_MODEL_PATH, *fx);
	//	���f���̐ݒ�
	SetModel(std::move(model));

	//	�����蔻��̐���
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(GetPos(), 1.0f);
	//	�����蔻��̏����X�V����
	sphereCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̐ݒ�
	SetCollisionObject(std::move(sphereCollider));
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void Balloon::Update(const float& elapsedTime)
{
	
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Balloon::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!GetIsHitActive()) return;

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
void Balloon::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!GetIsHitActive()) return;

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
void Balloon::DebugRender()
{
	//	�X�e�[�W�I�u�W�F�N�g�̎��
	ImGui::Text("Balloon");
	//	���ʃf�o�b�O�`��
	CommonDebugRender();
}

/// <summary>
/// �I��
/// </summary>
void Balloon::Finalize()
{

}

/// <summary>
/// ���Z�b�g
/// </summary>
void Balloon::Reset()
{
	//	�A�N�e�B�u��Ԃ�true��
	SetIsHitActive(true);
}

/// <summary>
/// �����
/// </summary>
void Balloon::Break()
{
	//	�j�􉹂̍Đ�
	GetAudioResources()->PlayBalloonSE();

	//	�A�N�e�B�u��Ԃ�false��
	SetIsHitActive(false);
}
