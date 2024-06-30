//--------------------------------------------------------------------------------------
// File: PlayerSpring.cpp
//
// �v���C���[�΂˃N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayerSpring.h"

#include "SpringState/SpringStateDefault.h"
#include "SpringState/SpringStateShrink.h"

#include "SpringParts/SpringPart.h"

#include "GameObjects/PlayScene/Player/PlayerHead.h"
#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/StageObjects/Balloon.h"
#include "GameObjects/PlayScene/StageObjects/Ground.h"

#include "GameObjects/PlayScene/Player/SpringParts/PredictionLine.h"

#include "GameObjects/PlayScene/Particle/Particle.h"

using namespace DirectX;

//	�f�[�^�A�N�Z�X������z��
const std::string PlayerSpring::DATA_STRING[DATA_NUMBER] = {
	"JumpForce",
	"Gravity",
	"ShrinkSpeed",
	"ExtendSpeed",
	"XZForceRatio"};

//	�����蔻��̔��a
const float PlayerSpring::COLLISION_RADIUS = 0.3f;
//	���̓����蔻��̈ʒu
const SimpleMath::Vector3 PlayerSpring::COLLISION_POSITION_OFFSET = SimpleMath::Vector3(0.0f, -0.5f, 0.0f);
//	���̈ʒu
const SimpleMath::Vector3 PlayerSpring::HEAD_POSITION_OFFSET = SimpleMath::Vector3(0.0f, 0.8f, 0.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[�N���X�̃|�C���^</param>
PlayerSpring::PlayerSpring(Player* p):
	PlayerComponent(p),
	m_nowSpringState(nullptr),
	m_nextSpringState(nullptr),
	m_isShrink(false),
	m_hitBalloon(nullptr),
	m_isGoal(false)
{
	//	�f�[�^�̓ǂݍ���
	m_springData = JsonManager::LoadFile(DataPath::PLAYER_SPRING_DATA_PATH);

	//	�f�[�^��ϐ��֊i�[
	m_jumpForce = m_springData[DATA_STRING[0]];
	m_gravity = m_springData[DATA_STRING[1]];
	m_shrinkRatio = m_springData[DATA_STRING[2]];
	m_extendSpeed = m_springData[DATA_STRING[3]];
	m_XZForceRatio = m_springData[DATA_STRING[4]];
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerSpring::~PlayerSpring()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
void PlayerSpring::Initialize(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	�p�[�c�̐���
	for (int i = 0; i < DataPath::PLAYER_SPRING_MODEL_NUMBER; i++)
	{
		//	��������
		std::unique_ptr<SpringPart> part = std::make_unique<SpringPart>();
		part->Initialize(DataPath::PLAYER_SPRING_MODEL_PATHs[i]);
		//	�z��֊i�[
		m_springParts.push_back(std::move(part));
	}

	//	�����蔻��̐���
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(
		position + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, rotate),
		COLLISION_RADIUS);
	//	�����蔻��̐ݒ�
	SetCollisionObject(std::move(sphereCollider));

	//	�v���C���[�̓�����
	m_head = std::make_unique <PlayerHead>(GetPlayer(), this);
	m_head->Initialize(
		position + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET, rotate),
		rotate);
	//	�q���̐ݒ�
	SetChild(m_head.get());

	//	�\�����̐���
	m_line = std::make_unique<PredictionLine>();
	m_line->Initialize();

	//	���Z�b�g
	Reset(position, rotate);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
/// <param name="stageObjects">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void PlayerSpring::Update(const float& elapsedTime, const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate, StageManager* stageManager)
{
	//	�\�����\���̐؂�ւ�
	ChangeDisplayLine();

	//	���͍X�V
	RotUpdate(elapsedTime);

	//	�΂ˏ�Ԃ̍X�V
	if (m_nowSpringState) m_nowSpringState->Update(elapsedTime);

	//	���̏�Ԃ����݂���
	if (m_nextSpringState)
	{
		//	��Ԃ̐ݒ�
		SetState(m_nextSpringState);
		//	���̏�Ԃ̍폜
		m_nextSpringState = nullptr;
		return;
	}

	//	���W���擾
	SimpleMath::Vector3 pos = GetPos();

	//	�����蔻��̍��W��ϊ�����
	GetCollisionObject()->ColliderUpdate(
		pos + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()));

	//	�����蔻��N���X
	Collider collider;

	//	�X�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻��
	for (auto stageObj : stageManager->GetStageObjs())
	{
		//	��A�N�e�B�u��ԂȂ珈�����Ȃ�
		if (!stageObj->GetIsHitActive()) continue;

		//	���D�̏ꍇ
		if (stageObj->GetStageObjType() == StageObjType::Balloon)
		{
			//	�Փ˔���
			if (!collider.SphereToSphereCheck(GetCollisionObject(), stageObj->GetCollisionObject())) continue;
			//	�߂荞�ݕ␳
			pos += InImmersed(collider.GetDistance());

			//	�G�ꂽ���D�̊i�[
			m_hitBalloon = dynamic_cast<Balloon*>(stageObj);
		}
		else
		{
			//	�Փ˔���
			if (!collider.SphereToBoxCheck(GetCollisionObject(), stageObj->GetCollisionObject())) continue;
			//	�߂荞�ݕ␳
			pos += InImmersed(collider.GetDistance());

			//	�_��h�炷
			if (!m_isShrink) dynamic_cast<Ground*>(stageObj)->SetIsShake(true);
		}

		//	�����蔻��̍��W��ϊ�����
		GetCollisionObject()->ColliderUpdate(
			pos + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()));

		//	�ՓˊJ�n����
		if (!m_isShrink)
		{
			//	�W�����v�p�[�e�B�N���̍Đ�
			GetPlayer()->GetJumpParticle()->Play(GetCollisionObject()->GetPos());
			//	�΂ˉ��̍Đ�
			GetAudioResources()->PlaySpringSE();
		}

		//	�k�����ɂ���
		m_isShrink = true;
		//	�k�ݏ�Ԃ֕ύX
		SetNextState(new SpringStateShrink(this));
	}

	//	�X�V����
	m_head->Update(
		elapsedTime,
		pos + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua(),
		stageManager);

	//	�S�[���̓����蔻��
	m_isGoal = collider.SphereToBoxCheck(GetCollisionObject(), stageManager->GetGoal()->GetCollisionObject());

	//	���W�̍X�V
	SetPos(pos);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayerSpring::Render(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	�\�����̕`��
	if(m_line->GetIsActive()) m_line->Render(view, proj);

	//	�΂˂̃p�[�c�̕`��
	for (auto& part : m_springParts)
	{
		part->Render(GetWorldMatrix(), view, proj);
	}

	//	�q���̕`��
	m_head->Render(view, proj);
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayerSpring::ShadowRender(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	�T�C�Y���|����
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	��]���|����
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	�ړ�������
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());
	//	���[���h�s��̐ݒ�
	SetWorldMatrix(sca * rot * trans);

	//	�΂˂̃p�[�c�̕`��
	for (auto& part : m_springParts)
	{
		part->ShadowRender(GetWorldMatrix(), view, proj);
	}

	//	�q���̕`��
	m_head->ShadowRender(view, proj);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void PlayerSpring::DebugRender()
{
	ImGui::InputFloat(DATA_STRING[0].c_str(), &m_jumpForce);
	ImGui::InputFloat(DATA_STRING[1].c_str(), &m_gravity);
	ImGui::SliderFloat(DATA_STRING[2].c_str(), &m_shrinkRatio, 0.980f, 0.999f);
	ImGui::SliderFloat(DATA_STRING[3].c_str(), &m_extendSpeed, 0.01f, 0.1f);
	ImGui::SliderFloat(DATA_STRING[4].c_str(), &m_XZForceRatio, 1.0f, 2.0f);

	//	���̃f�o�b�O�`��
	m_head->DebugRender();
}

/// <summary>
/// �I��
/// </summary>
void PlayerSpring::Finalize()
{
	//	��Ԃ̍폜
	DeleteState();

	//	�΂˂̃p�[�c�̏I��
	for (auto& part : m_springParts)
	{
		part->Finalize();
	}
	
	//	���̏I��
	m_head->Finalize();
}

//	���Z�b�g
void PlayerSpring::Reset(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	���W
	SetPos(position);
	//	��]
	SetRotQua(rotate);
	//	�g�嗦
	SetSca(SimpleMath::Vector3::One);

	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
	//	�J�[�\�����W��߂�
	SetCursorPos(centerPos.x, centerPos.y);

	//	�����蔻��̍X�V
	GetCollisionObject()->ColliderUpdate(
		GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()),
		GetRotQua(),
		GetSca());

	// ���̃��Z�b�g
	m_head->Reset(
		GetPos() + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua());

	//	�x�N�g���̃��Z�b�g
	m_velocity = SimpleMath::Vector3::Zero;
	//	�k�ݒ�
	m_isShrink = false;

	//	�\�����̃��Z�b�g
	m_line->Reset();

	//	�ʏ��Ԃ̐ݒ�
	SetState(new SpringStateDefault(this));
}
/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
void PlayerSpring::SaveData()
{
	//	�f�[�^��ϐ��֊i�[
	m_springData[DATA_STRING[0]] = m_jumpForce;
	m_springData[DATA_STRING[1]] = m_gravity;
	m_springData[DATA_STRING[2]] = m_shrinkRatio;
	m_springData[DATA_STRING[3]] = m_extendSpeed;
	m_springData[DATA_STRING[4]] = m_XZForceRatio;

	//	�f�[�^�̕ۑ�
	JsonManager::SaveFile(DataPath::PLAYER_SPRING_DATA_PATH, m_springData);

	//	���f�[�^�̕ۑ�
	m_head->SaveData();
}

/// <summary>
/// �e�X�g�X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void PlayerSpring::TestUpdate(const float& elapsedTime)
{
	//	���͍X�V
	RotUpdate(elapsedTime);

	//	�X�V����
	m_head->Update(
		elapsedTime,
		GetPos() + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua(),
		nullptr);
}

/// <summary>
/// ���̏�Ԃ̐ݒ�
/// </summary>
/// <param name="state">�΂ˏ�ԃN���X�̃|�C���^</param>
void PlayerSpring::SetNextState(SpringState* state)
{
	if (m_nextSpringState || !state) return;

	// �V�[���𐶐�
	m_nextSpringState = state;
}

/// <summary>
/// ��Ԃ̐ݒ�
/// </summary>
/// <param name="state">�΂ˏ�ԃN���X�̃|�C���^</param>
void PlayerSpring::SetState(SpringState* state)
{
	//	�|�C���^�������ꍇ�A�������Ȃ�
	if (!state) return;

	//	��Ԃ̍폜
	DeleteState();

	//	��Ԃ̐ݒ�
	m_nowSpringState = state;
	//	������
	m_nowSpringState->Initialize();
}

/// <summary>
///	���D�̔j��
/// </summary>
void PlayerSpring::BreakBalloon()
{
	//	���D�������ꍇ�A�������Ȃ�
	if (!m_hitBalloon) return;

	//	���D������
	m_hitBalloon->Break();
	m_hitBalloon = nullptr;
}

/// <summary>
/// ��Ԃ̍폜
/// </summary>
void PlayerSpring::DeleteState()
{
	//	�|�C���^�����݂��Ȃ��ꍇ�A�������Ȃ�
	if (!m_nowSpringState) return;
	
	//	�I��
	m_nowSpringState->Finalize();

	//	��Ԃ̍폜
	delete m_nowSpringState;
	//	nullptr�̊i�[
	m_nowSpringState = nullptr;
}

/// <summary>
/// ��]�X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void PlayerSpring::RotUpdate(const float& elapsedTime)
{
	//	�}�E�X�̌��݂̍��W
	Mouse::State mo = Mouse::Get().GetState();
	SimpleMath::Vector2 nowMousePos = SimpleMath::Vector2(mo.x, mo.y);

	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();

	//	�}�E�X�̈ړ���
	SimpleMath::Vector2 mouseVel = (nowMousePos - centerPos) * GetPlayer()->GetMouseSensitivity();

	//	�J�[�\�����W��߂�
	SetCursorPos(centerPos.x, centerPos.y);

	//if (mx <= 0 && my <= 0) return;

	//	��]��
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;

	//	��]�ʂ̌v�Z
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(-mouseVel.x));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(mouseVel.y));

	//	��]�̏�Z
	SimpleMath::Quaternion rotate = GetRotQua() * q;
	//	��]�̕ۑ�
	SetRotQua(rotate);

	//	�\�����v�Z(�k����)
	if(m_isShrink) PreLine(elapsedTime);
}
/// <summary>
/// �߂荞�ݕ␳
/// </summary>
/// <param name="distance">�߂荞�ݗ�</param>
/// <returns>�␳�x�N�g��</returns>
SimpleMath::Vector3 PlayerSpring::InImmersed(const float& distance)
{
	//	���]�x�N�g��
	SimpleMath::Vector3 vel = -m_velocity;
	//	�x�N�g���̐��K��
	vel.Normalize();

	//	�߂荞�ݗʂ̉����o��
	vel *= distance;
	//	���x�̑��E
	m_velocity *= 0.0f;

	return vel;
}

/// <summary>
/// �\�����\���̐؂�ւ�
/// </summary>
void PlayerSpring::ChangeDisplayLine()
{
	//	�L�[�{�[�h�X�e�[�g�g���b�J�[
	auto key = GetUserResources()->GetKeyboardStateTracker();

	//	X�L�[�������ꂽ�u��
	if (key->IsKeyPressed(Keyboard::Keys::X))
	{
		//	�\�����\���̐؂�ւ�
		bool flag = m_line->GetIsActive();
		m_line->SetIsActive(!flag);
		//	���Z�b�g
		m_line->Reset();
	}
}

/// <summary>
///	�\�����̌v�Z
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void PlayerSpring::PreLine(const float& elapsedTime)
{
	//	�v���p
	float timer = 0.0f;

	//	�z����N���A����
	m_line->Reset();

	//	���W�̎擾
	SimpleMath::Vector3 pos = GetPos();
	//	���˕Ԃ��
	SimpleMath::Vector3 vel = SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, m_jumpForce, 0.0f), GetRotQua());

	//	�R�b�Ԃ̍��W��\������
	while (timer < PredictionLine::PREDICTION_TIME)
	{
		//	���Ԃ̑���
		timer += elapsedTime;

		//	�d�͂̉��Z
		vel.y -= m_gravity;
		//	���x�̉��Z
		pos += (vel * elapsedTime);

		m_line->AddPosition(pos);
	}
}