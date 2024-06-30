//--------------------------------------------------------------------------------------
// File: PlayCamera.cpp
//
// �v���C�J�����N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayCamera.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/Player/PlayerSpring.h"

#include "imgui.h"

using namespace DirectX;

//	�f�[�^�A�N�Z�X������z��
const std::string PlayCamera::DATA_STRING[DATA_NUMBER] = {
	"OffSet",
	"MaxOffSet_X",
	"MaxOffSet_Z",
	"MinOffSet_Z",
	"TargetDistance"};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="startPos">�J�n���W</param>
/// <param name="endPos">�I�����W</param>
PlayCamera::PlayCamera(
	const DirectX::SimpleMath::Vector3& startPos,
	const DirectX::SimpleMath::Vector3& endPos) :
	m_swich(false),
	m_t(1.0f),
	m_timer(0.0f)
{
	//	�f�[�^�̓ǂݍ���
	m_cameraData = JsonManager::LoadFile(DataPath::PLAY_CAMERA_DATA_PATH);

	//	�f�[�^��ϐ��֊i�[
	m_offset = SimpleMath::Vector3(
		m_cameraData[DATA_STRING[0]][0],
		m_cameraData[DATA_STRING[0]][1],
		m_cameraData[DATA_STRING[0]][2]);
	m_maxOffset_x = m_cameraData[DATA_STRING[1]];
	m_maxOffset_z = m_cameraData[DATA_STRING[2]];
	m_minOffset_z = m_cameraData[DATA_STRING[3]];
	m_targetDistance = m_cameraData[DATA_STRING[4]];

	//	���W�̐ݒ�
	BeforeUpdate(0.0f, startPos, endPos, 1.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayCamera::~PlayCamera()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
void PlayCamera::Update(const float& elapsedTime, Player* player)
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	�b�L�[�������ꂽ��J�����̈ʒu��ύX
	if (kbTracker->pressed.C) m_swich = !m_swich;

	//	�I�t�Z�b�g�̕ύX
	ChangeOffset(elapsedTime);

	//	�v���C���[�΂˃N���X�ɃL���X�g
	PlayerSpring* spring = dynamic_cast<PlayerSpring*>(player->GetPlayerSpring());

	//	�v���C���[�̍��W
	SimpleMath::Vector3 pPos = spring->GetPos();
	//	�v���C���[��Y���W�g�嗦
	float pSca_y = spring->GetSca().y;
	//	�v���C���[�̑O������
	SimpleMath::Vector3 pForward = spring->GetCollisionObject()->GetForward();

	//	���W�̍X�V
	SimpleMath::Vector3 pos = EyeUpdate(pPos, pSca_y);
	//	�ڕW���W�̍X�V
	SimpleMath::Vector3 target = TargetUpdate(pPos, pForward, pSca_y);

	//	���W�̐ݒ�
	SetPos(pos);
	//	�ڕW���W�̐ݒ�
	SetTargetPosition(target);

	//	�r���[�s��̌v�Z
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(GetPos(), GetTargetPosition(), SimpleMath::Vector3::Up);
	//	�r���[�s��̐ݒ�
	SetViewMatrix(view);
}

/// <summary>
/// �J�n�O�X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="startPos">�J�n���W</param>
/// <param name="endPos">�I�����W</param>
/// <param name="duration">�Ԋu</param>
/// <returns>�X�V�I���t���O</returns>
bool PlayCamera::BeforeUpdate(
	const float& elapsedTime,
	const DirectX::SimpleMath::Vector3& startPos,
	const DirectX::SimpleMath::Vector3& endPos,
	const float& duration)
{
	//	�Ԋu��0�b�ȉ�
	if (duration <= 0.0f) return true;

	//	���Ԃ̑���
	m_timer += elapsedTime;

	//	���Ԃ̊���
	float t = m_timer / duration;

	//	���W�̌v�Z
	SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(endPos, startPos, t);
	//	�I�t�Z�b�g
	SimpleMath::Vector3 offset = m_offset + SimpleMath::Vector3(0.0f, 0.0f, m_maxOffset_z);

	//	���W�̐ݒ�
	SetPos(pos + offset);
	//	�ڕW���W�̐ݒ�
	SetTargetPosition(pos);

	//	�r���[�s��̌v�Z
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(GetPos(), GetTargetPosition(), SimpleMath::Vector3::Up);
	//	�r���[�s��̐ݒ�
	SetViewMatrix(view);

	if (m_timer > duration) return true;
	return false;
}

/// <summary>
/// �f�o�b�O�p�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayCamera::DebugRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	UI�̕`��
	ImGui::SetNextWindowPos(ImVec2(300, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_::ImGuiCond_Always);

	ImGui::Begin("PlayCamera");
	float offset[3] = { m_offset.x, m_offset.y, m_offset.z };
	ImGui::InputFloat3(DATA_STRING[0].c_str(), offset);
	m_offset = SimpleMath::Vector3(offset[0], offset[1], offset[2]);

	ImGui::InputFloat(DATA_STRING[1].c_str(), &m_maxOffset_x);
	ImGui::InputFloat(DATA_STRING[2].c_str(), &m_maxOffset_z);
	ImGui::InputFloat(DATA_STRING[3].c_str(), &m_minOffset_z);
	ImGui::InputFloat(DATA_STRING[4].c_str(), &m_targetDistance);

	ImGui::End();
}

/// <summary>
/// �I�t�Z�b�g�̕ύX
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void PlayCamera::ChangeOffset(const float& elapsedTime)
{
	if (m_swich && m_t > 0.0f)
	{
		m_t -= elapsedTime;
		if (m_t < 0.0f) m_t = 0.0f;
	}
	else if (!m_swich && m_t < 1.0f)
	{
		m_t += elapsedTime;
		if (m_t > 1.0f) m_t = 1.0f;
	}

	//	x���̂���̌v�Z
	m_offset.x = GetUserResources()->Lerp(-m_maxOffset_x, m_maxOffset_x, m_t);
}

/// <summary>
/// ���W�̍X�V
/// </summary>
/// <param name="pos">����W</param>
/// <param name="t">����</param>
/// <returns>���W</returns>
DirectX::SimpleMath::Vector3 PlayCamera::EyeUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const float& t)
{
	//	���W�̌v�Z
	return SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3(pos.x, pos.y + m_offset.y, pos.z - m_minOffset_z),
		SimpleMath::Vector3(pos.x, pos.y, pos.z + m_maxOffset_z) + m_offset,
		t);
}

/// <summary>
/// �ڕW���W�̍X�V
/// </summary>
/// <param name="pos">����W</param>
/// <param name="forward">���ʍ��W</param>
/// <param name="t">����</param>
/// <returns>�ڕW���W</returns>
DirectX::SimpleMath::Vector3 PlayCamera::TargetUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& forward,
	const float& t)
{
	//	���W�̌v�Z
	return SimpleMath::Vector3::Lerp(
		pos + (forward * m_targetDistance),
		pos,
		t);
}

/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
void PlayCamera::SaveData()
{
	//	�f�[�^�̍X�V
	m_cameraData[DATA_STRING[0]][0] = m_offset.x;
	m_cameraData[DATA_STRING[0]][1] = m_offset.y;
	m_cameraData[DATA_STRING[0]][2] = m_offset.z;
	m_cameraData[DATA_STRING[1]] = m_maxOffset_x;
	m_cameraData[DATA_STRING[2]] = m_maxOffset_z;
	m_cameraData[DATA_STRING[3]] = m_minOffset_z;
	m_cameraData[DATA_STRING[4]] = m_targetDistance;

	//	�f�[�^�̕ۑ�
	JsonManager::SaveFile(DataPath::PLAY_CAMERA_DATA_PATH, m_cameraData);
}