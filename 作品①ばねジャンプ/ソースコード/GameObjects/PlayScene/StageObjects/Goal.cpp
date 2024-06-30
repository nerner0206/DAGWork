//--------------------------------------------------------------------------------------
// File: Goal.cpp
//
// �S�[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Goal.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
Goal::Goal(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	Ground(pos, rot, sca)
{
	SetStageObjType(StageObjType::Goal);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Goal::~Goal()
{

}

/// <summary>
/// ������
/// </summary>
void Goal::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_GOAL_MODEL_PATH, *fx);
	//	���f����ݒ肷��
	SetModel(std::move(model));

	//	�����蔻��𐶐�
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̏����X�V����
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̐ݒ�
	SetCollisionObject(std::move(boxCollider));
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void Goal::DebugRender()
{
	//	�X�e�[�W�I�u�W�F�N�g�̎��
	ImGui::Text("Goal");
	//	���ʃf�o�b�O�`��
	CommonDebugRender();
}

/// <summary>
/// �I��
/// </summary>
void Goal::Finalize()
{
}
