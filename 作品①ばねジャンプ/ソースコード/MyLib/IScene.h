//--------------------------------------------------------------------------------------
// File: IScene.h
//
// �V�[�����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISCENE_DEFINED
#define ISCENE_DEFINED

#include"SceneManager.h"

#include "GameObjects/Common/SkyDome.h"

#include "MyLib/UserResources.h"
#include "MyLib/AudioResources.h"
#include "MyLib/UserInterface.h"

/// <summary>
/// �V�[�����N���X
/// </summary>
class IScene
{
public:
	//	�V�[���̎��
	enum class SceneKind
	{
		TitleScene,
		SelectScene,
		PlayScene
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	IScene(const SceneKind& kind) : 
		m_sceneManager(nullptr),
		m_lightRange(0.0f),
		m_kind(kind)
	{
		//	���[�U�[���\�[�X�̎擾
		m_ur = UserResources::GetInstance();
		//	�����\�[�X�̎擾
		m_ar = AudioResources::GetInstance();

		//	�X�J�C�h�[���̍쐬
		m_skyDome = std::make_unique<SkyDome>();
	}

	/// <summary>
	/// �V�[���Ǘ��N���X�̐ݒ�
	/// </summary>
	/// <param name="sceneManager">�V�[���Ǘ��N���X�̃|�C���^</param>
	void SetSceneManager(SceneManager* sceneManager) { m_sceneManager = sceneManager; }
	/// <summary>
	/// �V�[���Ǘ��N���X�̎擾
	/// </summary>
	/// <returns>�V�[���Ǘ��N���X�̃|�C���^</returns>
	SceneManager* GetSceneManager() { return m_sceneManager; }

	/// <summary>
	/// ���[�U�[���\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	UserResources* GetUserResources() { return m_ur; }

	/// <summary>
	/// �����\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>�����\�[�X�N���X�̃|�C���^</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// �X�J�C�h�[���N���X�̐ݒ�
	/// </summary>
	/// <param name="skyDome">�X�J�C�h�[���N���X�̃��j�[�N�|�C���^</param>
	void SetSkyDome(std::unique_ptr<SkyDome> skyDome) { m_skyDome = std::move(skyDome); }
	/// <summary>
	/// �X�J�C�h�[���N���X�̎擾
	/// </summary>
	/// <returns>�X�J�C�h�[���N���X�̃|�C���^</returns>
	SkyDome* GetSkyDome() { return m_skyDome.get(); }

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
	/// <summary>
	/// �ˉe�s��̎擾
	/// </summary>
	/// <returns>�ˉe�s��</returns>
	const DirectX::SimpleMath::Matrix GetProjMatrix() { return m_proj; }
	/// <summary>
	/// �ˉe�s��̐ݒ�
	/// </summary>
	/// <param name="proj">�ˉe�s��</param>
	void SetProjMatrix(const DirectX::SimpleMath::Matrix& proj) { m_proj = proj; }

	/// <summary>
	/// ���C�g�̍��W�̎擾
	/// </summary>
	/// <returns>���C�g���W</returns>
	const DirectX::SimpleMath::Vector3 GetLightPos() { return m_lightPos; }
	/// <summary>
	/// ���C�g�̍��W�̐ݒ�
	/// </summary>
	/// <param name="lightPos">���C�g���W</param>
	void SetLightPos(const DirectX::SimpleMath::Vector3& lightPos) { m_lightPos = lightPos; }
	/// <summary>
	/// ���C�g�̖ڕW���W�̎擾
	/// </summary>
	/// <returns>���C�g�ڕW���W</returns>
	const DirectX::SimpleMath::Vector3 GetLightTarget() { return m_lightTarget; }
	/// <summary>
	/// ���C�g�̖ڕW���W�̐ݒ�
	/// </summary>
	/// <param name="lightTarget">���C�g�ڕW���W</param>
	void SetLightTarget(const DirectX::SimpleMath::Vector3& lightTarget) { m_lightTarget = lightTarget; }
	/// <summary>
	/// ���C�g�̉e���͈͂̎擾
	/// </summary>
	/// <returns>���C�g�̉e���͈�</returns>
	const float GetLightRange() { return m_lightRange; }
	/// <summary>
	/// ���C�g�̉e���͈͂̐ݒ�
	/// </summary>
	/// <param name="lightRange">���C�g�̉e���͈�</param>
	void SetLightRange(const float& lightRange) { m_lightRange = lightRange; }

	/// <summary>
	/// �J�����̍��W���擾
	/// </summary>
	/// <returns>�J�����̍��W</returns>
	const DirectX::SimpleMath::Vector3 GetCameraPos() { return m_cameraPos; }
	/// <summary>
	/// �J�����̍��W��ݒ�
	/// </summary>
	/// <param name="cameraPos">�J�����̍��W</param>
	void SetCameraPos(const DirectX::SimpleMath::Vector3& cameraPos) { m_cameraPos = cameraPos; }
	/// <summary>
	/// �J�����̖ڕW���W���擾
	/// </summary>
	/// <returns>�J�����̖ڕW���W</returns>
	const DirectX::SimpleMath::Vector3 GetCameraTarget() { return m_cameraTarget; }
	/// <summary>
	/// �J�����̖ڕW���W��ݒ�
	/// </summary>
	/// <param name="cameraTarget">�J�����̖ڕW���W</param>
	void SetCameraTarget(const DirectX::SimpleMath::Vector3& cameraTarget) { m_cameraTarget = cameraTarget; }

	//	�V�[���̎�ނ̎擾
	const SceneKind GetSceneKind() { return m_kind; }

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	virtual void Initialize(const int& mouseNumber) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Render() = 0;
	/// <summary>
	/// �e�`��
	/// </summary>
	virtual void ShadowRender() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;

private:
	// �V�[���Ǘ��N���X�̃|�C���^
	SceneManager* m_sceneManager;

	//	���[�U�[���\�[�X�N���X�̃|�C���^
	UserResources* m_ur;
	//	�����\�[�X�N���X�̃|�C���^
	AudioResources* m_ar;

	//	�V�[���̎��
	SceneKind m_kind;

	//	�X�J�C�h�[���̃��j�[�N�|�C���^
	std::unique_ptr<SkyDome> m_skyDome;

	//	�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//	�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	// ���C�g�̍��W
	DirectX::SimpleMath::Vector3 m_lightPos;
	// ���C�g�̖ڕW���W
	DirectX::SimpleMath::Vector3 m_lightTarget;
	// ���C�g�̉e���͈�
	float m_lightRange;

	//	�J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPos;
	//	�J�����̖ڕW���W
	DirectX::SimpleMath::Vector3 m_cameraTarget;
};
#endif // !ISCENE_DEFINED