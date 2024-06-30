//--------------------------------------------------------------------------------------
// File: SphereCollider.cpp
//
// ���̓����蔻��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SphereCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">�����蔻��̍��W</param>
/// <param name="radius">���̔��a</param>
SphereCollider::SphereCollider(const DirectX::SimpleMath::Vector3& pos, const float& radius) :
	CollisionObject(CollisionType::Sphere, pos),
	m_radius(radius)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	
	//	���̍쐬(���a)
	m_geometricPrimitive = GeometricPrimitive::CreateSphere(context, m_radius * 2.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SphereCollider::~SphereCollider()
{

}

/// <summary>
/// �����蔻��̍X�V
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rotate">��]</param>
/// <param name="sca">�g�嗦</param>
void SphereCollider::ColliderUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Quaternion& rotate,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	���W�̍X�V
	SetPos(pos);
}

/// <summary>
/// �����蔻��̕`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void SphereCollider::ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();

	//	���[���h�s��̌v�Z
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	���W
	world*= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	�W�I���g���̕`��
	m_geometricPrimitive->Draw(world, view, proj, Colors::White * 0.5f);
}