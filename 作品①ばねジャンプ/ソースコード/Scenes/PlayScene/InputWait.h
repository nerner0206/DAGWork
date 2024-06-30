//--------------------------------------------------------------------------------------
// File: InputWait.h
//
// ���͑ҋ@��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef INPUT_WAIT_DEFINED
#define INPUT_WAIT_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class SpaceUI;
class CounterUI;

/// <summary>
/// ���͑ҋ@��ԃN���X
/// </summary>
class InputWait : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	InputWait(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~InputWait();

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
	//	�X�y�[�XUI�̃��j�[�N�|�C���^
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	�J�E���^�[UI�̃��j�[�N�|�C���^
	std::unique_ptr<CounterUI> m_counterUI;
};
#endif // !INPUT_WAIT_DEFINED
