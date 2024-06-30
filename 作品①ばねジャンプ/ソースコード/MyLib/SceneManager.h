//--------------------------------------------------------------------------------------
// File: SceneManager.h
//
// �V�[���Ǘ��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SCENE_MANAGER_DEFINED
#define SCENE_MANAGER_DEFINED

#include "MyLib/JsonManager.h"

class IScene;
class SystemWindow;
class FadeCloud;

/// <summary>
///	�V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	//	�V�[���J��
	enum class SceneState
	{
		FadeIn,		//	�t�F�C�h�C��
		Main,		//	���C��
		FadeOut		//	�t�F�C�h�A�E�g
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime);
	/// <summary>
	///	�`��
	/// </summary>
	void Render();
	/// <summary>
	///	�e�`��
	/// </summary>
	void ShadowRender();

	/// <summary>
	/// �V�[����ݒ�i�����j
	/// </summary>
	/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
	void SetScene(IScene* scene);
	/// <summary>
	/// ���̃V�[����ݒ�i�V�[���ړ��j
	/// </summary>
	/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
	void SetNextScene(IScene* scene);

	/// <summary>
	/// �V�[����Ԃ��擾
	/// </summary>
	/// <returns>�V�[�����</returns>
	const SceneState& GetSceneState() { return m_sceneState; }

	/// <summary>
	/// �V�X�e���ݒ�̕ۑ�
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	void SaveSystem(const int& mouseNumber);

private:
	//	�f�[�^�A�N�Z�X�p�̕�����
	static const std::string DATA_STR;

private:
	//	���݂̃V�[���|�C���^
	IScene* m_nowScene;
	//	���̃V�[���|�C���^
	IScene* m_nextScene;

	//	�V�[�����
	SceneState m_sceneState;

	//	�t�F�C�h�摜
	std::unique_ptr<FadeCloud> m_fade;
	//	�ݒ���
	std::unique_ptr<SystemWindow> m_system;

	//	json�t�@�C��
	nlohmann::json m_systemData;

private:
	/// <summary>
	/// �V�[���̍폜
	/// </summary>
	void DeleteScene();
	/// <summary>
	/// �C���Q�[���̏���
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void MainUpdate(const float& elapsedTime);
};
#endif // !SCENE_MANAGER_DEFINED