//--------------------------------------------------------------------------------------
// File: StageManager.h
//
// �X�e�[�W�Ǘ��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef STAGE_MANAGER_DEFINED
#define STAGE_MANAGER_DEFINED

#include "IStageObject.h"
#include "Start.h"
#include "MyLib/JsonManager.h"

class Player;

/// <summary>
/// �X�e�[�W�Ǘ��N���X
/// </summary>
class StageManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StageManager();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	void Initialize(const int& stageNum, Player* player);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	void DebugRender();
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();
	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	void SaveData(const int& stageNum);

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�N���X�̃|�C���^�z��
	/// </summary>
	/// <returns>�X�e�[�W�I�u�W�F�N�g�N���X�̃|�C���^�z��</returns>
	std::vector<IStageObject*> GetStageObjs() { return m_stageObjs; }

	/// <summary>
	/// �S�[���̎擾
	/// </summary>
	/// <returns>�S�[���N���X�̃|�C���^</returns>
	IStageObject* GetGoal() { return m_goal.get(); }

	/// <summary>
	/// �������W�̎擾
	/// </summary>
	/// <returns>�������W</returns>
	const DirectX::SimpleMath::Vector3& GetStartPosition() { return Start::START_POSITION; }

public:
	//	json�t�@�C���̍ŏ��̕�����
	const static std::string FIRST_STR;

	const static int OBJ_INFO_NUM = 4;
	//	json�t�@�C���̕�����
	const static std::string OBJ_INFO_STR[OBJ_INFO_NUM];

private:
	//	json�t�@�C��
	nlohmann::json m_stageData;

	//	�X�^�[�g�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Start> m_start;
	//	�S�[���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<IStageObject> m_goal;
	//	�X�e�[�W�I�u�W�F�N�g�N���X�̃|�C���^�z��
	std::vector<IStageObject*> m_stageObjs;
	//	���N���X�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<IStageObject>> m_winds;

	//	�X�e�[�W�I�u�W�F�N�g�N���X�̃|�C���^�z��
	std::vector<IStageObject*> m_debugObjs;

	//	�f�o�b�O�ԍ�
	int m_debugNumber;

private:

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�̐���
	/// </summary>
	/// <param name="objNum">�I�u�W�F�N�g�ԍ�</param>
	/// <param name="type">�X�e�[�W���</param>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]�x�N�g��</param>
	/// <param name="sca">�g�嗦</param>
	void CreateObj(
		const int& objNum,
		const StageObjType& type,
		Player* player,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
};
#endif // !STAGE_MANAGER_DEFINED
