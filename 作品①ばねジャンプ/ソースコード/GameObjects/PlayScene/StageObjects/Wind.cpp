//--------------------------------------------------------------------------------------
// File: Wind.cpp
//
// ���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Wind.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/Particle/WindParticle.h"

using namespace DirectX;

//	�f�[�^�A�N�Z�X�p������
const std::string Wind::POWER_STR = "Power";

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <param name="power">����</param>
Wind::Wind(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& power) :
	IStageObject(StageObjType::Wind, pos, rot, sca),
	m_power(power),
	m_isHit(false),
	m_player(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wind::~Wind()
{

}

/// <summary>
/// ������
/// </summary>
void Wind::Initialize()
{
	//	�����蔻��̐���
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());
	//	�����蔻��̏����X�V����
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̐ݒ�
	SetCollisionObject(std::move(boxCollider));

	//	������
	m_vector = SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, GetRotQua());

	//	�p�[�e�B�N���̐���
	m_windParticle = std::make_unique<WindParticle>(this);
	//	������
	m_windParticle->Initialize();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void Wind::Update(const float& elapsedTime)
{
	//	�����蔻��
	Collider collider;

	//	�v���C���[�̓����蔻��
	if (collider.BoxToBoxCheck(m_player->GetBoxCollider(), GetCollisionObject()))
	{
		//	�ՓˊJ�n����
		if (!m_isHit)
		{
			//	�����̍Đ�
			GetAudioResources()->PlayWindSE();
			//	�Փˍς�
			m_isHit = true;
		}

		//	�v���C���[�΂˃N���X�փL���X�g
		PlayerSpring* spring = dynamic_cast<PlayerSpring*>(m_player->GetPlayerSpring());

		//	���x�̉��Z
		spring->AddVelocity(m_vector * m_power * elapsedTime);
	}
	else
	{
		//	�Փ˂��Ă��Ȃ�
		m_isHit = false;
	}

	//	�p�[�e�B�N���̍X�V
	m_windParticle->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Wind::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�p�[�e�B�N���̕`��
	m_windParticle->Render(view, proj);
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Wind::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{

}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void Wind::DebugRender()
{
	//	�X�e�[�W�I�u�W�F�N�g�̎��
	ImGui::Text("Wind");
	//	���ʃf�o�b�O�`��
	CommonDebugRender();
	//	���͂̕ύX
	ImGui::InputFloat(POWER_STR.c_str(), &m_power);
}

/// <summary>
/// �I��
/// </summary>
void Wind::Finalize()
{
	//	�p�[�e�B�N���̏I������
	m_windParticle->Finalize();
}

/// <summary>
/// ���Z�b�g
/// </summary>
void Wind::Reset()
{

}