//--------------------------------------------------------------------------------------
// File: SphereCollider.h
//
// ���̓����蔻��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPHERE_COLLIDER_DEFINED
#define SPHERE_COLLIDER_DEFINED

#include "CollisionObject.h"

/// <summary>
/// ���̓����蔻��N���X
/// </summary>
class SphereCollider : public CollisionObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����蔻��̍��W</param>
	/// <param name="radius">���̔��a</param>
	SphereCollider(const DirectX::SimpleMath::Vector3& pos, const float& radius);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SphereCollider();

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
	/// ���a�̐ݒ�
	/// </summary>
	/// <param name="r">���̔��a</param>
	void SetRadius(const float& r) { m_radius = r; }
	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <returns>���̔��a</returns>
	float GetRadius() const { return m_radius; }

private:
	//	�W�I���g���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	//	���̔��a
	float m_radius;
};
#endif // !SPHERE_COLLIDER_DEFINED