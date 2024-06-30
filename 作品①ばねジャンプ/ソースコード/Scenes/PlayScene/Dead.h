//--------------------------------------------------------------------------------------
// File: Dead.h
//
// ���S��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DEAD_DEFINED
#define DEAD_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class Dead : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	Dead(PlayScene* scene, PlayCamera* camera);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Dead();

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
	//	���SUI�̊g�嗦
	static const float DEAD_SCALE;

private:
	//	���SUI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_deadUI;
	//	����UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_blackUI;

	//	�������t���O
	bool m_init;
	//	����
	float m_timer;
};
#endif // !DEAD_DEFINED
