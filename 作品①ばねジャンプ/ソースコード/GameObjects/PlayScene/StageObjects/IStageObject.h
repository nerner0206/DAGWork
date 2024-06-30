//--------------------------------------------------------------------------------------
// File: IStageObject.h
//
// �X�e�[�W�I�u�W�F�N�g���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISTAGE_OBJECT_DEFINED
#define ISTAGE_OBJECT_DEFINED

#include "GameObjects/Object.h"
#include "GameObjects/PlayScene/CollisionObjects/CollisionObject.h"

#include "imgui.h"

#include <vector>

//	�X�e�[�W�I�u�W�F�N�g���
enum class StageObjType
{
	Goal = 0,		//	�S�[��
	Cloud,			//	�_
	MoveCloud,		//	�����_
	Wind,			//	��
	Balloon,		//	���D

	OverID
};

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g���N���X
/// </summary>
class IStageObject : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�X�e�[�W�I�u�W�F�N�g���</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	IStageObject(
		const StageObjType& type,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) :
		Object(pos, CalculationRot(rot), sca),
		m_type(type),
		m_isHitActive(true),
		m_collision(nullptr)
	{

	}

	/// <summary>
	/// ��]�x�N�g���̎擾
	/// </summary>
	/// <returns>��]�x�N�g��</returns>
	const DirectX::SimpleMath::Vector3 GetRot() { return m_rotVec; }
	/// <summary>
	/// ��]�x�N�g���̐ݒ�
	/// </summary>
	/// <param name="rot">��]�x�N�g��</param>
	void SetRot(const DirectX::SimpleMath::Vector3& rotVec) { m_rotVec = rotVec; }

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g��ނ̎擾
	/// </summary>
	/// <returns>�X�e�[�W�I�u�W�F�N�g���</returns>
	const StageObjType GetStageObjType() { return m_type; }
	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g��ނ̐ݒ�
	/// </summary>
	/// <param name="type">�X�e�[�W�I�u�W�F�N�g���</param>
	void SetStageObjType(const StageObjType& type) { m_type = type; }

	/// <summary>
	/// ���f���̎擾
	/// </summary>
	/// <returns>���f���̃|�C���^</returns>
	DirectX::Model* GetModel() { return m_model.get(); }
	/// <summary>
	/// ���f���̐ݒ�
	/// </summary>
	/// <param name="model">���f���̃|�C���^</param>
	void SetModel(std::unique_ptr<DirectX::Model> model) { m_model = std::move(model); }

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	const DirectX::SimpleMath::Matrix GetWorldMatrix() { return m_world; }
	/// <summary>
	/// ���[���h�s��̐ݒ�
	/// </summary>
	/// <param name="world">���[���h�s��</param>
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	/// <returns>�����蔻����N���X�̃|�C���^</returns>
	CollisionObject* GetCollisionObject() { return m_collision.get(); }
	/// <summary>
	/// �����蔻��̐ݒ�
	/// </summary>
	/// <param name="obj">�����蔻����N���X�̃|�C���^</param>
	void SetCollisionObject(std::unique_ptr<CollisionObject> obj) { m_collision = std::move(obj); }

	/// <summary>
	/// ���ʃf�o�b�O�`��
	/// </summary>
	void CommonDebugRender()
	{
		using namespace DirectX;

		//	���W�̎擾
		SimpleMath::Vector3 pos = GetPos();
		ImGui::Text("Position");
		ImGui::InputFloat("P_X", &pos.x);
		ImGui::InputFloat("P_Y", &pos.y);
		ImGui::InputFloat("P_Z", &pos.z);

		//	��]�̎擾
		SimpleMath::Vector3 rot = GetRot();
		ImGui::Text("Rotation");
		if (ImGui::InputFloat("R_X", &rot.x))
		{
			//	��]�N�H�[�^�j�I���̌v�Z
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}
		else if (ImGui::InputFloat("R_Y", &rot.y))
		{
			//	��]�N�H�[�^�j�I���̌v�Z
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}
		else if (ImGui::InputFloat("R_Z", &rot.z))
		{
			//	��]�N�H�[�^�j�I���̌v�Z
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}

		SimpleMath::Vector3 sca = GetSca();
		ImGui::Text("Scale");
		ImGui::InputFloat("S_X", &sca.x);
		ImGui::InputFloat("S_Y", &sca.y);
		ImGui::InputFloat("S_Z", &sca.z);

		SetPos(pos);
		SetRot(rot);
		SetSca(sca);
	}

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IStageObject() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	virtual void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	virtual void DebugRender() = 0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	virtual void Reset() = 0;

	/// <summary>
	/// �A�N�e�B�u��Ԃ̎擾
	/// </summary>
	/// <returns>�A�N�e�B�u���</returns>
	const bool& GetIsHitActive() { return m_isHitActive; }
	/// <summary>
	/// �A�N�e�B�u��Ԃ̐ݒ�
	/// </summary>
	/// <param name="flag">�A�N�e�B�u���</param>
	void SetIsHitActive(const bool& flag) { m_isHitActive = flag; }

private:
	/// <summary>
	/// ��]�̌v�Z
	/// </summary>
	/// <param name="rot">��]�x�N�g��</param>
	/// <returns>��]�N�H�[�^�j�I��</returns>
	const DirectX::SimpleMath::Quaternion& CalculationRot(const DirectX::SimpleMath::Vector3& rot)
	{
		using namespace DirectX;

		//	��]�N�H�[�^��I��
		SimpleMath::Quaternion rotate = SimpleMath::Quaternion::Identity;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;

		//	��]���|����
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(rot.z));
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(rot.x));
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(rot.y));
		
		//	��]�̌v�Z
		rotate = q * rotate;
		return rotate;
	}

private:
	//	���
	StageObjType m_type;
	//	��]�x�N�g��
	DirectX::SimpleMath::Vector3 m_rotVec;

	//	�����蔻��̗L��
	bool m_isHitActive;

	//	���f��
	std::unique_ptr<DirectX::Model> m_model;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//	�����蔻��
	std::unique_ptr<CollisionObject> m_collision;
};
#endif		// ISTAGE_OBJECT_DEFINED