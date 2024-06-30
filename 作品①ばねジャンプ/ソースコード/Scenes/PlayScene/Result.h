//--------------------------------------------------------------------------------------
// File: Result.h
//
// ���U���g��ԃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef RESULT_DEFINED
#define RESULT_DEFINED

#include "Scenes/PlayScene/IPlaySceneState.h"

class Particle;
class SpaceUI;
class CounterUI;

class Result : public IPlaySceneState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�v���C�V�[���N���X�̃|�C���^</param>
	/// <param name="camera">�v���C�J�����N���X�̃|�C���^</param>
	/// <param name="resultTime">���ʎ���</param>
	Result(PlayScene* scene, PlayCamera* camera, const float& resultTime);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Result();

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
	//	����UI�̍��W
	static const DirectX::SimpleMath::Vector2 COUNTER_POSITION;

private:
	//	������p�[�e�B�N��
	std::unique_ptr<Particle> m_confettiParticle;

	//	���U���gUI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_resultUI;

	//	�X�y�[�XUI�̃��j�[�N�|�C���^
	std::unique_ptr<SpaceUI> m_spaceUI;
	//	�J�E���^�[UI�̃��j�[�N�|�C���^
	std::unique_ptr<CounterUI> m_counterUI;

	//	�J�E���^�[
	int m_resultTime;
};
#endif // !RESULT_DEFINED
