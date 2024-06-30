//--------------------------------------------------------------------------------------
// File: InGame.h
//
// �Q�[������ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef INGAME_DEFINED
#define INGAME_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class CounterUI;

class InGame : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	InGame(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~InGame();

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
	//	UI�̊g�嗦
	static const float UI_SCALE;

	//	�A�C�R����Y���W
	static const int ICON_Y = 715;
	//	�{�^����Y���W
	static const int BUTTON_Y = 720;

	//	X�{�^����X���W
	static const int X_ICON_X = 0;
	//	C�{�^����X���W
	static const int C_ICON_X = 175;

	//	�{�^���̋���
	static const int BUTTON_DISTANCE = 100;

private:
	//	C�A�C�R���E�{�^��UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_C_IconUI;
	std::unique_ptr<UserInterface> m_C_ButtonUI;

	//	X�A�C�R���E�{�^��UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_X_IconUI;
	std::unique_ptr<UserInterface> m_X_ButtonUI;

	//	�J�E���^�[UI�̃��j�[�N�|�C���^
	std::unique_ptr<CounterUI> m_counterUI;
	//	�^�C�}�[
	float m_timer;
};
#endif // !INGAME_DEFINED
