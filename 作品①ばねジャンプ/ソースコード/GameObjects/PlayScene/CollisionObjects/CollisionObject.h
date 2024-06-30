//--------------------------------------------------------------------------------------
// File: CollisionObject.h
//
// �����蔻����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef COLLISION_OBJECT_DEFINED
#define COLLISION_OBJECT_DEFINED

#include "GameObjects/Object.h"

#include <GeometricPrimitive.h>

//	�����蔻����
enum class CollisionType
{
	Sphere = 0,
	Box,

	OverID
};

/// <summary>
/// �����蔻����N���X
/// </summary>
class CollisionObject : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�����蔻��̎��</param>
	/// <param name="pos">�����蔻��̍��W</param>
	/// <param name="rot">�����蔻��̉�]</param>
	/// <param name="sca">�����蔻��̊g�嗦</param>
	CollisionObject(
		const CollisionType& type,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rot = DirectX::SimpleMath::Quaternion::Identity,
		const DirectX::SimpleMath::Vector3& sca = DirectX::SimpleMath::Vector3::One) :
		Object(pos, rot, sca),
		m_type(type)
	{

	}

	//	��ނ̎擾
	const CollisionType GetCollisionType() { return m_type; }
	//	��ނ̐ݒ�
	void SetCollisionType(const CollisionType& type) { m_type = type; }

	/// <summary>
	/// ���ʕ����̎擾
	/// </summary>
	/// <returns>���ʕ����̃x�N�g��</returns>
	const DirectX::SimpleMath::Vector3 GetForward() { return m_forward; }
	/// <summary>
	/// ���ʕ����̐ݒ�
	/// </summary>
	/// <param name="forward">���ʕ����̃x�N�g��</param>
	void SetForward(const DirectX::SimpleMath::Vector3& forward) { m_forward = forward; }
	/// <summary>
	/// ���������̎擾
	/// </summary>
	/// <returns>���������̃x�N�g��</returns>
	const DirectX::SimpleMath::Vector3 GetHorizontal() { return m_horizontal; }
	/// <summary>
	/// ���������̐ݒ�
	/// </summary>
	/// <param name="horizontal">���������̃x�N�g��</param>
	void SetHorizontal(const DirectX::SimpleMath::Vector3& horizontal) { m_horizontal = horizontal; }
	/// <summary>
	///	���������̎擾
	/// </summary>
	/// <returns>���������̃x�N�g��</returns>
	const DirectX::SimpleMath::Vector3 GetVertical() { return m_vertical; }
	/// <summary>
	/// ���������̐ݒ�
	/// </summary>
	/// <param name="vertical">���������̃x�N�g��</param>
	void SetVertical(const DirectX::SimpleMath::Vector3& vertical) { m_vertical = vertical; }

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CollisionObject() = default;

	/// <summary>
	/// �����蔻��̍X�V
	/// </summary>
	/// <param name="pos">�����蔻��̍��W</param>
	/// <param name="rotate">�����蔻��̉�]</param>
	/// <param name="sca">�����蔻��̊g�嗦</param>
	virtual void ColliderUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotate = DirectX::SimpleMath::Quaternion::Identity,
		const DirectX::SimpleMath::Vector3& sca = DirectX::SimpleMath::Vector3::One) = 0;
	/// <summary>
	/// �����蔻��̕`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	virtual void ColliderRender(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj) = 0;

private:
	//	�����蔻����
	CollisionType m_type;

	//	���ʕ����̃x�N�g��
	DirectX::SimpleMath::Vector3 m_forward;
	//	��������
	DirectX::SimpleMath::Vector3 m_horizontal;
	//	��������
	DirectX::SimpleMath::Vector3 m_vertical;
};
#endif // !COLLISION_OBJECT_DEFINED