//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// �v���C���[�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Player.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/Player/PlayerHead.h"

#include "GameObjects/PlayScene/Particle/JumpParticle.h"
#include "GameObjects/PlayScene/Particle/ExplosionParticle.h"

using namespace DirectX;

//	�����蔻��̃I�t�Z�b�g
const SimpleMath::Vector3 Player::COLLISION_POSITION_OFFSET = SimpleMath::Vector3(0.0f, 0.25f, 0.0f);
//	�����蔻��̊g�嗦
const SimpleMath::Vector3 Player::COLLISION_SCALE = SimpleMath::Vector3(1.0f, 2.0f, 1.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() :
	m_playerSpring(nullptr),
	m_mouseSensitivity(1.0f),
	m_isGoal(false),
	m_isDead(false)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="startPos">�������W</param>
void Player::Initialize(const DirectX::SimpleMath::Vector3& startPos)
{
	//	�������W�̏�����
	m_startPos = startPos;

	//	�΂˂̐���
	m_playerSpring = std::make_unique<PlayerSpring>(this);
	//	�΂˂̏�����
	m_playerSpring->Initialize(
		m_startPos,
		SimpleMath::Quaternion::Identity);

	//	�����蔻��̐���
	m_boxCollider = std::make_unique<BoxCollider>(
		m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
		m_playerSpring->GetRotQua(),
		COLLISION_SCALE);

	//	�t���O�̏�����
	m_isGoal = false;
	m_isDead = false;

	//	�W�����v�p�[�e�B�N���̐���
	m_jumpParticle = std::make_unique<JumpParticle>();
	m_jumpParticle->Initialize();
	//	�����p�[�e�B�N���̐���
	m_explosionParticle = std::make_unique<ExplosionParticle>();
	m_explosionParticle->Initialize();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="stageObjs">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void Player::Update(const float& elapsedTime, StageManager* stageManager)
{
	//	���̃|�C���^�ɃL���X�g
	PlayerHead* head = dynamic_cast<PlayerHead*>(m_playerSpring->GetChild());

	if (!head->GetHit())
	{
		//	�΂˂̍X�V
		m_playerSpring->Update(
			elapsedTime,
			SimpleMath::Vector3::Zero,
			SimpleMath::Quaternion::Identity,
			stageManager);

		//	�����蔻��̍X�V
		m_boxCollider->ColliderUpdate(
			m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
			m_playerSpring->GetRotQua(),
			COLLISION_SCALE);
	}

	//	�΂˂̃|�C���^�ɃL���X�g
	PlayerSpring* spring = dynamic_cast<PlayerSpring*>(m_playerSpring.get());

	//	�v���C���[�̎��S����
	if ((head->GetHit() && !m_explosionParticle->GetActive()) ||
		m_playerSpring->GetPos().y < -10.0f)
	{
		//	���S��Ԃɂ���
		m_isDead = true;

		//	�I��
		return;
	}

	//	�S�[������i�΂˕����̂݁j
	m_isGoal = spring->GetIsGoal();
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//	�΂˂̕`��
	m_playerSpring->Render(view, proj);
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Player::ShadowRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//	�e�`��
	m_playerSpring->ShadowRender(view, proj);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void Player::DebugRender()
{
	//	�E�B���h�E�F�̐ݒ�
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_::ImGuiCond_Always);

	//	�E�B���h�E�̐ݒ�
	ImGui::Begin("Player");

	//	�΂˂̃f�o�b�O�`��
	m_playerSpring->DebugRender();

	//	�E�B���h�E�̏I��
	ImGui::End();

	//	�F�̏�����
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

/// <summary>
/// �I��
/// </summary>
void Player::Finalize()
{
	//	�΂˂̏I������
	m_playerSpring->Finalize();
}

/// <summary>
/// ���Z�b�g����
/// </summary>
void Player::Reset()
{
	//	�΂˂����Z�b�g
	m_playerSpring->Reset(
		m_startPos,
		SimpleMath::Quaternion::Identity);

	//	�����蔻��̍X�V
	m_boxCollider->ColliderUpdate(
		m_playerSpring->GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, m_playerSpring->GetRotQua()),
		m_playerSpring->GetRotQua());

	//	�ϐ��̃��Z�b�g
	m_isGoal = false;
	m_isDead = false;
}
/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
void Player::SaveData()
{
	//	�΂˃f�[�^�̕ۑ�
	m_playerSpring->SaveData();
}