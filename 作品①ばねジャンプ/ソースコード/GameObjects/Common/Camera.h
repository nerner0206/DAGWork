//--------------------------------------------------------------------------------------
// File: Camera.h
//
// �J�������N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef CAMERA_DEFINED
#define CAMERA_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// �J�������N���X
/// </summary>
class Camera : public Object
{
public:
	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	Camera() :
		Object(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One),
		m_up(DirectX::SimpleMath::Vector3::Up) { }

	/// <summary>
	///	�J�����̖ڕW���W�̎擾
	/// </summary>
	/// <returns>�ڕW���W</returns>
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	/// <summary>
	/// �J�����̖ڕW���W�̐ݒ�
	/// </summary>
	/// <param name="target">�ڕW���W</param>
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { m_target = target; }

	/// <summary>
	///	�J�����̏�����̎擾
	/// </summary>
	/// <returns>�����</returns>
	const DirectX::SimpleMath::Vector3& GetUp() { return m_up; }
	/// <summary>
	/// �J�����̏�����̐ݒ�
	/// </summary>
	/// <param name="up">�����</param>
	void SetUp(const DirectX::SimpleMath::Vector3& up) { m_up = up; }

	/// <summary>
	/// �r���[�s��̎擾
	/// </summary>
	/// <returns>�r���[�s��</returns>
	const DirectX::SimpleMath::Matrix GetViewMatrix() { return m_view; }
	/// <summary>
	/// �r���[�s��̐ݒ�
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }

public:
	/// <summary>
	///	���z�f�X�g���N�^
	/// </summary>
	virtual ~Camera() = default;

private:
	//	�J�����̖ڕW���W
	DirectX::SimpleMath::Vector3 m_target;
	//	�J�����̏����
	DirectX::SimpleMath::Vector3 m_up;

	//	�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
};
#endif // !CAMERA_DEFINED
