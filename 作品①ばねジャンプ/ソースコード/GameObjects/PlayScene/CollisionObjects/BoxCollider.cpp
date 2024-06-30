//--------------------------------------------------------------------------------------
// File: BoxCollider.cpp
//
// ���̓����蔻��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BoxCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]</param>
/// <param name="sca">�g�嗦</param>
BoxCollider::BoxCollider(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	CollisionObject(CollisionType::Box, pos, rot, sca)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	
	//	���̍쐬
	m_geometricPrimitive = GeometricPrimitive::CreateBox(context, SimpleMath::Vector3::One);

	//	���a
	float r = (sca / 2.0f).Length();

	//	�g�嗦�ɉ��������̓����蔻��̍쐬
	m_sphereCollider = std::make_unique<SphereCollider>(pos, r);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoxCollider::~BoxCollider()
{

}

/// <summary>
/// �����蔻��̍X�V
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rotate">��]</param>
/// <param name="sca">�g�嗦</param>
void BoxCollider::ColliderUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rotate,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	���W�̍X�V
	SetPos(pos);
	//	��]�̍X�V
	SetRotQua(rotate);
	//	�g�嗦�̍X�V
	SetSca(sca);

	//	�e���̌v�Z
 	SetForward(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -1.0f), rotate));
	SetHorizontal(SimpleMath::Vector3::Transform(SimpleMath::Vector3(1.0f, 0.0f, 0.0f), rotate));
	SetVertical(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 1.0f, 0.0f), rotate));

	//	�e�ʂ̖@���x�N�g���̌v�Z
	m_normal[0] = -GetForward();
	m_normal[1] = -GetHorizontal();
	m_normal[2] = GetVertical();
	m_normal[3] = -GetVertical();
	m_normal[4] = GetHorizontal();
	m_normal[5] = GetForward();

	//	���̓����蔻��̍X�V
	m_sphereCollider->ColliderUpdate(pos, rotate, sca);
}

/// <summary>
/// �����蔻��̕`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void BoxCollider::ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();

	//	���[���h�s��̌v�Z
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	�g�嗦
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	��]
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	���W
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	world = sca * rot * trans;

	//	�W�I���g���̕`��
	m_geometricPrimitive->Draw(world, view, proj, Colors::White * 0.5f);

	//	���̕`��
	m_sphereCollider->ColliderRender(view, proj);
}