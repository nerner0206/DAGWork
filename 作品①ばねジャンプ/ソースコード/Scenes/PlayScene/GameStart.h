//--------------------------------------------------------------------------------------
// File: GameStart.h
//
// �Q�[���J�n��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef GAMEStart_DEFINED
#define GAMEStart_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class SpaceUI;
class CounterUI;

/// <summary>
/// �Q�[���J�n��ԃN���X
/// </summary>
class GameStart : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	GameStart(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameStart();

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
	//	���[��UI�̍��W
	static const DirectX::SimpleMath::Vector2 RULU_POSITION;

private:
	//	���[���摜
	std::unique_ptr<UserInterface> m_ruluUI;

	//	�X�y�[�XUI�̃��j�[�N�|�C���^
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	�J�E���^�[UI�̃��j�[�N�|�C���^
	std::unique_ptr<CounterUI> m_counterUI;
};
#endif // !IGAMEStart_DEFINED
