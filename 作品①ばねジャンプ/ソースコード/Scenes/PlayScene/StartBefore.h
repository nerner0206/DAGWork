//--------------------------------------------------------------------------------------
// File: StartBefore.h
//
// �J�n�O��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef START_BEFORE_DEFINED
#define START_BEFORE_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

/// <summary>
/// �J�n�O��ԃN���X
/// </summary>
class StartBefore : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	StartBefore(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StartBefore();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	void Initialize(Player* player, StageManager* stageManager) override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="stageManager">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
	void Update(const float& elapsedTime, Player* player, StageManager* stageManager) override;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

private:
	//	�J�������x
	static const float CAMERA_SPEED;

private:
	//	�X�^�[�g���W
	DirectX::SimpleMath::Vector3 m_startPos;
	//	�S�[�����W
	DirectX::SimpleMath::Vector3 m_goalPos;

	//	�ړ�����
	float m_time;
};
#endif // !INPUT_WAIT_DEFINED
