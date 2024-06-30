//--------------------------------------------------------------------------------------
// File: PlayScene.h
//
// �v���C�V�[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAY_SCENE_DEFINED
#define PLAY_SCENE_DEFINED

#include "MyLib/IScene.h"

#include <vector>

class IPlaySceneState;

class Player;
class StageManager;

class PlayCamera;
class DebugCamera;

class BigCloud;
class Particle;

/// <summary>
/// �v���C�V�[���N���X
/// </summary>
class PlayScene : public IScene
{
public:
	//	�v���C�V�[�����[�h
	enum class PlaySceneMode
	{
		PlayMode = 0,
		DebugMode
	};

	//	�X�y�[�XUI�̍��W
	static const DirectX::SimpleMath::Vector2 SPACE_POSITION;
	//	����UI�̍��W
	static const DirectX::SimpleMath::Vector2 COUNTER_POSITION;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="num">�X�e�[�W�ԍ�</param>
	PlayScene(const int& stageNum);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayScene();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	void Initialize(const int& mouseNumber) override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// �`��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowRender() override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �v���C�V�[����Ԃ̐ݒ�
	/// </summary>
	/// <param name="state">�v���C�V�[����ԃN���X�̃|�C���^</param>
	void SetState(IPlaySceneState* state);
	/// <summary>
	/// ���̃v���C�V�[����Ԃ̐ݒ�
	/// </summary>
	/// <param name="state">�v���C�V�[����ԃN���X�̃|�C���^</param>
	void SetNextState(IPlaySceneState* state);

	/// <summary>
	/// �v���C���[�̎擾
	/// </summary>
	/// <returns>�v���C���[�N���X�̃|�C���^</returns>
	Player* GetPlayer() { return m_player.get(); }

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="particle">�p�[�e�B�N���N���X�̃|�C���^</param>
	void AddParticle(Particle* particle) { m_particles.push_back(particle); }

	/// <summary>
	/// �}�E�X���x�̐ݒ�
	/// </summary>
	/// <param name="num">�}�E�X���x</param>
	void SetMouseSpeed(const int& mouseNumber);

private:
	//	���C�g�̍��W
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	//	���C�g�̉e���͈�
	static const float LIGHT_RANGE;

	//	�傫���_�̍��W
	static const DirectX::SimpleMath::Vector3 BIG_CLOUD_POSITION;
	//	�傫���_�̊g�嗦
	static const float BIG_CLOUD_SCALE;

	//	�X�e�[�WUI�̋���
	static const int STAGE_DISTANCE = 30;
	//	�X�e�[�W�ԍ�UI�̊g�嗦
	static const float STAGE_NUMBER_SCALE;

private:
	//	���݂̃��[�h
	PlaySceneMode m_mode;

	//	���݂̃v���C�V�[����Ԃ̃|�C���^
	IPlaySceneState* m_nowState;
	//	���̃v���C�V�[����Ԃ̃|�C���^
	IPlaySceneState* m_nextState;

	//	�v���C���[�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Player> m_player;
	//	�X�e�[�W�Ǘ��N���X�̃��j�[�N�|�C���^
	std::unique_ptr<StageManager> m_stageManager;
	//	�X�e�[�W�ԍ�
	int m_stageNum;

	//	�v���C�V�[���J�����N���X�̃��j�[�N�|�C���^
	std::unique_ptr<PlayCamera> m_playCamera;
	//	�f�o�b�O�J�����N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DebugCamera> m_debugCamera;

	//	�傫���_�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<BigCloud> m_bigCloud;

	//	�p�[�e�B�N���N���X�̃|�C���^�z��
	std::vector<Particle*> m_particles;

	//	�X�e�[�WUI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_stageUI;
	//	�X�e�[�W�ԍ�UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_stageNumUI;

private:
	/// <summary>
	/// �v���C�V�[����Ԃ̍폜
	/// </summary>
	void DeletePlaySceneState();

	/// <summary>
	/// UI�̐���
	/// </summary>
	void CreateUI();

	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	void SaveData();
};
#endif		// PLAY_SCENE_DEFINED