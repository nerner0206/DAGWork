//--------------------------------------------------------------------------------------
// File: BoxCollider.h
//
// ���̓����蔻��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BOX_COLLIDER_DEFINED
#define BOX_COLLIDER_DEFINED

#include "SphereCollider.h"

/// <summary>
/// ���̓����蔻��N���X
/// </summary>
class BoxCollider : public CollisionObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="sca">�g�嗦</param>
	BoxCollider(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot,
		const DirectX::SimpleMath::Vector3& sca);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BoxCollider();
	
	/// <summary>
	/// �����蔻��̍X�V
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rotate">��]</param>
	/// <param name="sca">�g�嗦</param>
	void ColliderUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Vector3& sca) override;
	/// <summary>
	/// �����蔻��̕`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ColliderRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �@���x�N�g���̐ݒ�
	/// </summary>
	/// <param name="vel">�@���x�N�g��</param>
	/// <param name="num">�ʂ̔ԍ�</param>
	void SetNormal(const DirectX::SimpleMath::Vector3& vel, const int& num) { if (num >= 0 && num < 6) m_normal[num] = vel; }
	/// <summary>
	/// �@���x�N�g���̎擾
	/// </summary>
	/// <param name="num">�ʂ̔ԍ�</param>
	/// <returns>�@���x�N�g��</returns>
	DirectX::SimpleMath::Vector3 GetNormal(const int& num) const { 
		if (num >= 0 && num < 6) return m_normal[num]; 
		return DirectX::SimpleMath::Vector3::Zero; }

	/// <summary>
	/// ���̓����蔻��̎擾
	/// </summary>
	/// <returns>���̓����蔻��N���X�̃|�C���^</returns>
	SphereCollider* GetSphereCollider() { return m_sphereCollider.get(); }

private:
	//	�W�I���g���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	//	�ʂ̖@���x�N�g��
	DirectX::SimpleMath::Vector3 m_normal[6];

	//	���̓����蔻��N���X�̃��j�[�N�|�C���^
	std::unique_ptr<SphereCollider> m_sphereCollider;
};
#endif // !BOX_COLLIDER_DEFINED