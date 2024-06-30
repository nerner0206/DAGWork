//--------------------------------------------------------------------------------------
// File: PlayerHead.cpp
//
// �v���C���[���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayerHead.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"

#include "GameObjects/PlayScene/Particle/Particle.h"

using namespace DirectX;

//	���̃f�t�H���g�T�C�Y
const SimpleMath::Vector3 PlayerHead::PLAYER_HEAD_SIZE = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[�N���X�̃|�C���^</param>
/// <param name="parent">�e�̃|�C���^</param>
PlayerHead::PlayerHead(Player* p, PlayerComponent* parent) :
	PlayerComponent(p),
	m_hit(false)
{
	//	�e�|�C���^�̐ݒ�
	SetParent(parent);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHead::~PlayerHead()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
void PlayerHead::Initialize(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	m_model = Model::CreateFromCMO(device, DataPath::PLAYER_HEAD_MODEL_PATH, *fx);

	//	���̓����蔻��̍쐬
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(position, 0.45f);
	//	�����蔻��̐ݒ�
	SetCollisionObject(std::move(sphereCollider));

	//	���Z�b�g����
	Reset(position, rotate);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]</param>
/// <param name="stageObjects">�X�e�[�W�Ǘ��N���X�̃|�C���^</param>
void PlayerHead::Update(const float& elapsedTime, const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate, StageManager* stageManager)
{
	//	���W�̍X�V
	SetPos(position);
	//	��]�̍X�V
	SetRotQua(rotate);

	//	�����蔻��̍X�V
	GetCollisionObject()->ColliderUpdate(GetPos());

	//	nullptr�̏ꍇ�A�������Ȃ�
	if (stageManager == nullptr) return;

	//	�X�e�[�W�I�u�W�F�N�g�𐔂�����
	for (auto stageObj : stageManager->GetStageObjs())
	{
		//	�����蔻��p�N���X
		Collider collider;

		//	�Փ˔���
		if (collider.SphereToSphereCheck(GetCollisionObject(), stageObj->GetCollisionObject()) ||
			collider.SphereToBoxCheck(GetCollisionObject(), stageObj->GetCollisionObject()))
		{
			//	�Փ�
			m_hit = true;
			//	�p�[�e�B�N���̍Đ�
			GetPlayer()->GetExplosionParticle()->Play(GetPos());

			//	�v���C���[�ړ��ʂ̍폜
			PlayerSpring* spring = dynamic_cast<PlayerSpring*>(GetParent());
			spring->SetVelocity(SimpleMath::Vector3::Zero);
		}
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayerHead::Render(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	�Փˎ��`�悵�Ȃ�
	if (m_hit) return;

	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	���f���̕`��
	m_model->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, true);
		});
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayerHead::ShadowRender(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	�Փˎ��`�悵�Ȃ�
	if (m_hit) return;

	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�V���h�E�}�b�v�̎擾
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	�T�C�Y���|����
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(0.5f);
	//	��]���|����
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	�ړ�������
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	���[���h�s����v�Z����
	SimpleMath::Matrix world = sca * rot * trans;

	//	���f���̕`��
	m_model->Draw(context, *states, world, view, proj, false, [&]() 
		{
			shadowMap->DrawShadowMap(context);
		});

	//	���[���h�s���ݒ肷��
	SetWorldMatrix(world);
}

/// <summary>
///	�f�o�b�O�`��
/// </summary>
void PlayerHead::DebugRender()
{
	
}

/// <summary>
/// �I��
/// </summary>
void PlayerHead::Finalize()
{
	m_model.reset();
}

//	���Z�b�g
void PlayerHead::Reset(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	�ʒu���X�V
	SetPos(position);
	//	��]���X�V
	SetRotQua(rotate);

	//	�����蔻��̍��W��ϊ�����
	GetCollisionObject()->ColliderUpdate(GetPos());

	//	����̏�����
	m_hit = false;
}

/// <summary>
/// �f�[�^�̕ۑ�
/// </summary>
void PlayerHead::SaveData()
{

}