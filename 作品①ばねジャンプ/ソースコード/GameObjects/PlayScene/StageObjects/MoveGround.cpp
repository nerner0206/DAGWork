//--------------------------------------------------------------------------------------
// File: MoveGround.cpp
//
// ��������N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "MoveGround.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

//	�f�[�^�A�N�Z�X�p������
const std::string MoveGround::POSITIONS_STR = "PositionList";
//	�f�[�^�A�N�Z�X�p������
const std::string MoveGround::SPEED_STR = "Speed";

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos">���W</param>
/// <param name="rot">��]�x�N�g��</param>
/// <param name="sca">�g�嗦</param>
/// <param name="speed">���x</param>
MoveGround::MoveGround(
	const std::vector<DirectX::SimpleMath::Vector3>& poses,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& speed) :
	Ground(poses[0], rot, sca),
	m_poses(poses),
	m_speed(speed),
	m_num(0),
	m_nextNum(1),
	m_time(1.0f),
	m_timer(0.0f)
{
	SetStageObjType(StageObjType::MoveCloud);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MoveGround::~MoveGround()
{

}

/// <summary>
/// ������
/// </summary>
void MoveGround::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_CLOUD_MODEL_PATH, *fx);
	//	���f���̐ݒ�
	SetModel(std::move(model));

	//	�����蔻��𐶐�
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	�����蔻��̏����X�V����
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	�����蔻���ݒ肷��
	SetCollisionObject(std::move(boxCollider));

	m_num = 0;
	m_nextNum = 1;

	//	�ڕW�ւ̋���
	float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
	//	�ڕW�܂Ŋ|���鎞��
	m_time = length / m_speed;

	//	�^�C�}�[�̏�����
	m_timer = 0;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void MoveGround::Update(const float& elapsedTime)
{
	//	�_�̗h��
	Shaking(elapsedTime);

	//	���Ԃ̑���
	m_timer += elapsedTime;
	if (m_timer > m_time) m_timer = m_time;

	//	���W�̌v�Z
	SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(
		m_poses[m_num],
		m_poses[m_nextNum],
		m_timer / m_time);

	//	���̖ڕW���W��
	if (m_timer >= m_time)
	{
		//	���̍��W�ԍ���
		m_num++;
		if (m_num >= m_poses.size()) m_num = 0;
		m_nextNum = m_num + 1;
		if (m_nextNum >= m_poses.size()) m_nextNum = 0;

		//	�ڕW�ւ̋���
		float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
		//	�ڕW�܂Ŋ|���鎞��
		m_time = length / m_speed;

		//	�^�C�}�[�̏�����
		m_timer = 0;
	}

	//	���W�̐ݒ�
	SetPos(pos);

	//	�����蔻��̍X�V
	GetCollisionObject()->ColliderUpdate(GetPos(), GetRotQua(), GetSca());
}


/// <summary>
/// �f�o�b�O�`��
/// </summary>
void MoveGround::DebugRender()
{
	//	�X�e�[�W�I�u�W�F�N�g�̎��
	ImGui::Text("MoveCloud");
	//	���ʃf�o�b�O�`��
	CommonDebugRender();
	//	���x�̕ύX
	ImGui::InputFloat(SPEED_STR.c_str(), &m_speed);
}

/// <summary>
/// �I��
/// </summary>
void MoveGround::Finalize()
{

}

/// <summary>
/// ���Z�b�g
/// </summary>
void MoveGround::Reset()
{
	//	���W�̐ݒ�
	SetPos(m_poses[0]);

	m_num = 0;
	m_nextNum = 1;

	//	�ڕW�ւ̋���
	float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
	//	�ڕW�܂Ŋ|���鎞��
	m_time = length / m_speed;

	//	�^�C�}�[�̏�����
	m_timer = 0;
}
