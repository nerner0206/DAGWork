//--------------------------------------------------------------------------------------
// File: PlayerComponent.h
//
// �v���C���[���i�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAYER_COMPONENT_DEFINED
#define PLAYER_COMPONENT_DEFINED

#include "GameObjects/PlayScene/CollisionObjects/CollisionObject.h"

#include "imgui.h"

#include <vector>

class StageManager;
class Player;

/// <summary>
/// �v���C���[���i�N���X
/// </summary>
class PlayerComponent : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	PlayerComponent(Player* player) :
		Object(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One),
		m_player(player),
		m_parent(nullptr),
		m_child(nullptr),
		m_collision(nullptr)
	{

	}

	/// <summary>
	/// �e�̎擾
	/// </summary>
	/// <returns>�v���C���[���i�N���X�̃|�C���^</returns>
	PlayerComponent* GetParent() { return m_parent; }
	/// <summary>
	/// �e�̐ݒ�
	/// </summary>
	/// <param name="parent">�v���C���[���i�N���X�̃|�C���^</param>
	void SetParent(PlayerComponent* parent) { m_parent = parent; }

	/// <summary>
	/// �q�̎擾
	/// </summary>
	/// <returns>�v���C���[���i�N���X�̃|�C���^</returns>
	PlayerComponent* GetChild() { return m_child; }
	/// <summary>
	/// �q�̐ݒ�
	/// </summary>
	/// <param name="child">�v���C���[���i�N���X�̃|�C���^</param>
	void SetChild(PlayerComponent* child) { m_child = child; }

	/// <summary>
	///	���̓����蔻��̎擾
	/// </summary>
	/// <returns>�����蔻��N���X�̃|�C���^</returns>
	CollisionObject* GetCollisionObject() { return m_collision.get(); }
	/// <summary>
	/// ���̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="obj">�����蔻��N���X�̃|�C���^</param>
	void SetCollisionObject(std::unique_ptr<CollisionObject> obj) { m_collision = std::move(obj); }
	
	/// <summary>
	///	���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	const DirectX::SimpleMath::Matrix GetWorldMatrix() { return m_world; }
	/// <summary>
	///	���[���h�s��̐ݒ�
	/// </summary>
	/// <param name="world">���[���h�s��</param>
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/// <summary>
	/// �v���C���[�̎擾
	/// </summary>
	/// <returns>�v���C���[�N���X�̃|�C���^</returns>
	Player* GetPlayer() { return m_player; }

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual	~PlayerComponent() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	virtual void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	/// <param name="stageObjects">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	virtual void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		StageManager* stageManager) = 0;
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
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	virtual void Reset(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate) = 0;

	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	virtual void SaveData() = 0;

private:
	//	�v���C���[�N���X�̃|�C���^
	Player* m_player;

	//	�e�N���X
	PlayerComponent* m_parent;
	//	�q�N���X
	PlayerComponent* m_child;

	//	���̓����蔻��
	std::unique_ptr<CollisionObject> m_collision;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
};
#endif		// PLAYER_COMPONENT_DEFINED