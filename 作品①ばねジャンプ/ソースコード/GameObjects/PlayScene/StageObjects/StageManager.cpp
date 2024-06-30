//--------------------------------------------------------------------------------------
// File: StageManager.cpp
//
// �X�e�[�W�Ǘ��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StageManager.h"

#include "GameObjects/PlayScene/StageObjects/Factory/StageFactory.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/Start.h"

#include <sstream>

//	json�t�@�C���̍ŏ��̕�����
const std::string StageManager::FIRST_STR = "StageObj_list";
//	json�t�@�C���̕�����
const std::string StageManager::OBJ_INFO_STR[OBJ_INFO_NUM] = { "Type", "Position", "Rotation", "Scale" };

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageManager::StageManager() :
	m_debugNumber(0)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageManager::~StageManager()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="stageNum">�X�e�[�W�ԍ�</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
void StageManager::Initialize(const int& stageNum, Player* player)
{
	//	�X�e�[�Wjson�̓ǂݍ���
	m_stageData = JsonManager::LoadFile(DataPath::STAGE_DATA_PATHs[stageNum]);

	//	�X�^�[�g�̐���
	m_start = std::make_unique<Start>();
	m_start->Initialize();

	//	�X�e�[�W�I�u�W�F�N�g�̐�
	int objNum = m_stageData[FIRST_STR].size();
	//	�X�e�[�W�I�u�W�F�N�g�̐�������������
	for (int i = 0; i < objNum; i++)
	{
		//	�I�u�W�F�N�g�̎��
		int type_num = m_stageData[FIRST_STR][i][OBJ_INFO_STR[0]];

		//	�I�u�W�F�N�g�̍��W
		SimpleMath::Vector3 pos = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][2]);
		//	�I�u�W�F�N�g�̉�]
		SimpleMath::Vector3 rot = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][2]);
		//	�I�u�W�F�N�g�̃T�C�Y
		SimpleMath::Vector3 size = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][2]);
		
		//	�X�e�[�W�I�u�W�F�N�g�̐���
		CreateObj(i, static_cast<StageObjType>(type_num), player, pos, rot, size);
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void StageManager::Update(const float& elapsedTime)
{
	for (auto& obj : m_stageObjs)
	{
		//	�X�e�[�W�u���b�N�̍X�V
		obj->Update(elapsedTime);
	}

	//	���̍X�V
	for (auto& wind : m_winds)
	{
		wind->Update(elapsedTime);
	}

	//	�S�[���̍X�V
	m_goal->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void StageManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& obj : m_stageObjs)
	{
		//	�X�e�[�W�u���b�N�̍X�V
		obj->Render(view, proj);
	}

	//	���̍X�V
	for (auto& wind : m_winds)
	{
		wind->Render(view, proj);
	}

	//	�S�[���̕`��
	m_goal->Render(view, proj);
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void StageManager::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& obj : m_stageObjs)
	{
		//	�X�e�[�W�u���b�N�̍X�V
		obj->ShadowRender(view, proj);
	}

	m_goal->ShadowRender(view, proj);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void StageManager::DebugRender()
{
	//	�E�B���h�E�̐ݒ�
	ImGui::SetNextWindowPos(ImVec2(980, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 350), ImGuiCond_::ImGuiCond_Always);

	ImGui::Begin("StageObject");

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) 
	{ 
		m_debugNumber--;
		if (m_debugNumber < 0) m_debugNumber = m_debugObjs.size() - 1;
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
		m_debugNumber++;
		if (m_debugNumber >= m_debugObjs.size()) m_debugNumber = 0;
	}
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_debugNumber + 1);

	m_debugObjs[m_debugNumber]->DebugRender();

	ImGui::End();
}

/// <summary>
/// �I��
/// </summary>
void StageManager::Finalize()
{
	//	�S�Ẵ|�C���^������
	for (auto& debugObj : m_debugObjs)
	{
		debugObj = nullptr;
	}
	//	�z����폜����
	m_debugObjs.clear();

	for (int i = 0; i < m_stageObjs.size(); i++)
	{
		//	�X�e�[�W�u���b�N�̏I������
		m_stageObjs[i]->Finalize();
		//	�폜����
		delete m_stageObjs[i];
	}

	//	���̍X�V
	for (auto& wind : m_winds)
	{
		wind->Finalize();
	}
	
	//	�N���A
	m_stageObjs.clear();

	m_goal->Finalize();
}

/// <summary>
/// ���Z�b�g
/// </summary>
void StageManager::Reset()
{
	//	�X�e�[�W�I�u�W�F�N�g�̃��Z�b�g
	for (auto& obj : m_stageObjs)
	{
		obj->Reset();
	}
}

/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
/// <param name="stageNum">�X�e�[�W�ԍ�</param>
void StageManager::SaveData(const int& stageNum)
{
	//	��{���̕ۑ�
	for (int i = 0; i < m_debugObjs.size(); i++)
	{
		//	���W�̕ύX
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][0] = m_debugObjs[i]->GetPos().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][1] = m_debugObjs[i]->GetPos().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][2] = m_debugObjs[i]->GetPos().z;
		//	��]�̕ύX
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][0] = m_debugObjs[i]->GetRot().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][1] = m_debugObjs[i]->GetRot().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][2] = m_debugObjs[i]->GetRot().z;
		//	�g�嗦�̕ύX
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][0] = m_debugObjs[i]->GetSca().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][1] = m_debugObjs[i]->GetSca().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][2] = m_debugObjs[i]->GetSca().z;

		//	��
		if (m_debugObjs[i]->GetStageObjType() == StageObjType::Wind)
			m_stageData[FIRST_STR][i][Wind::POWER_STR] = dynamic_cast<Wind*>(m_debugObjs[i])->GetPower();
		//	�����_
		else if (m_debugObjs[i]->GetStageObjType() == StageObjType::MoveCloud)
		{
			//	���x
			m_stageData[FIRST_STR][i][MoveGround::SPEED_STR] = dynamic_cast<MoveGround*>(m_debugObjs[i])->GetSpeed();
		}
	}

	//	�ۑ�
	JsonManager::SaveFile(DataPath::STAGE_DATA_PATHs[stageNum], m_stageData);
}

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g�̐���
/// </summary>
/// <param name="objNum">�I�u�W�F�N�g�ԍ�</param>
/// <param name="type">�X�e�[�W���</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
void StageManager::CreateObj(
	const int& objNum,
	const StageObjType& type,
	Player* player,
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	�S�[��
	if (type == StageObjType::Goal)
	{
		//	����
		m_goal = StageFactory::CreateGoal(pos, rot, sca);
		//	�f�o�b�O�p�z��֊i�[
		m_debugObjs.push_back(m_goal.get());

		//	�����I��
		return;
	}

	//	��
	if (type == StageObjType::Wind)
	{
		//	����
		std::unique_ptr<Wind> wind = StageFactory::CreateWind(pos, rot, sca,
			m_stageData[FIRST_STR][objNum][Wind::POWER_STR]);
		//	�v���C���[�̐ݒ�
		wind->SetPlayer(player);
		//	�z��֊i�[
		m_winds.push_back(std::move(wind));
		//	�f�o�b�O�p�z��֊i�[
		m_debugObjs.push_back(m_winds[m_winds.size() - 1].get());

		//	�����I��
		return;
	}

	//	�i�[�p�N���X
	IStageObject* stageObj = nullptr;

	//	���ʉ_
	if (type == StageObjType::Cloud)
		stageObj = StageFactory::CreateGround(pos, rot, sca);

	//	�����_
	else if (type == StageObjType::MoveCloud)
	{
		//	�ړ���̔z��
		std::vector<SimpleMath::Vector3> poses;
		//	�ŏ��̍��W�̒ǉ�
		poses.push_back(pos);

		//	�ړ����W�̐�
		int posNum = m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR].size();

		for (int i = 0; i < posNum; i++)
		{
			//	���W
			SimpleMath::Vector3 position = SimpleMath::Vector3(
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][0],
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][1],
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][2]);

			//	���W�̒ǉ�
			poses.push_back(position);
		}

		//	���x
		stageObj = StageFactory::CreateMoveGround(poses, rot, sca,
			m_stageData[FIRST_STR][objNum][MoveGround::SPEED_STR]);
	}

	//	���D
	else if(type == StageObjType::Balloon)
		stageObj = StageFactory::CreateBalloon(pos, rot, sca);
	
	//	nullptr�Ȃ珈�����Ȃ�
	if (stageObj == nullptr) return;

	//	�z��Ɋi�[����
	m_stageObjs.push_back(stageObj);
	//	�f�o�b�O�p�z��֊i�[
	m_debugObjs.push_back(stageObj);
}