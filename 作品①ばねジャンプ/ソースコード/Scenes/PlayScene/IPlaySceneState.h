//--------------------------------------------------------------------------------------
// File: IPlaySceneState.h
//
// �v���C�V�[���̏�ԑJ�ڊ��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef IPLAY_SCENE_STATE_DEFINED
#define IPLAY_SCENE_STATE_DEFINED

#include "Scenes/PlayScene.h"

#include "Game/DataPath.h"

/// <summary>
/// �v���C�V�[���̏�ԑJ�ڊ��N���X
/// </summary>
class IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	IPlaySceneState(PlayScene* scene, PlayCamera* camera) :
		m_playScene(scene),
		m_playCamera(camera),
		m_ur(UserResources::GetInstance()),
		m_ar(AudioResources::GetInstance()) { }

	/// <summary>
	/// ���[�U�[���\�[�X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	UserResources* GetUserResources() { return m_ur; }
	/// <summary>
	/// ���[�U�[���\�[�X�̎擾
	/// </summary>
	/// <returns>���[�U�[���\�[�X�N���X�̃|�C���^</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// �v���C�V�[���̎擾
	/// </summary>
	/// <returns>�v���C�V�[���N���X�̃|�C���^</returns>
	PlayScene* GetPlayScene() { return m_playScene; }
	/// <summary>
	/// �v���C�J�����̎擾
	/// </summary>
	/// <returns>�v���C�J�����N���X�̃|�C���^</returns>
	PlayCamera* GetPlayCamera() { return m_playCamera; }

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IPlaySceneState() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	virtual void Initialize(Player* player, StageManager* stageManager) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	virtual void Update(const float& elapsedTime, Player* player, StageManager* stageManager) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;

private:
	//	���[�U�[���\�[�X�N���X�̃|�C���^
	UserResources* m_ur;
	//	�����\�[�X�N���X�̃|�C���^
	AudioResources* m_ar;

	//	�v���C�V�[��
	PlayScene* m_playScene;

	//	�v���C�J����
	PlayCamera* m_playCamera;
};
#endif // !IPLAY_SCENE_STATE_DEFINED