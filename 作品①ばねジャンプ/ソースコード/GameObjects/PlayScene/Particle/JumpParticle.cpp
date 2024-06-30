//--------------------------------------------------------------------------------------
// File: JumpParticle.cpp
//
// �W�����v�p�[�e�B�N���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "JumpParticle.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
const VertexPositionTexture JumpParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.25f, 0.25f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.25f, 0.25f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.25f, -0.25f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.25f, -0.25f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cam">�J�����N���X�̃|�C���^</param>
JumpParticle::JumpParticle() :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One),
	m_timer(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
JumpParticle::~JumpParticle()
{

}

/// <summary>
/// ������
/// </summary>
void JumpParticle::Initialize()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();

	// �G�t�F�N�g�̍쐬 
	m_batchEffect = std::make_unique<AlphaTestEffect>(device);
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);

	// ���̓��C�A�E�g���� 
	void const* shaderByteCode;
	size_t byteCodeLength;

	//	���_���
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(
		VertexPositionTexture::InputElements,
		VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()
	);

	// �v���~�e�B�u�o�b�`�̍쐬 
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// �e�N�X�`���̃��[�h 
	CreateWICTextureFromFile(
		device,
		DataPath::CLOUD_PARTICLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);

	//	�p�[�e�B�N���̐�������������
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	���W�̒ǉ�
		m_particlePos.push_back(SimpleMath::Vector3::Zero);
		//	�x�N�g���̒ǉ�
		m_particleVel.push_back(SimpleMath::Vector3::Zero);
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void JumpParticle::Update(const float& elapsedTime)
{
	//	�^�C�}�[�𑝉�
	m_timer += elapsedTime;

	//	�g�嗦�̌v�Z
	SimpleMath::Vector3 sca = SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3::One * 2.0f,
		SimpleMath::Vector3::Zero,
		m_timer);
	//	�g�嗦�̐ݒ�
	SetSca(sca);

	//	1�b���~
	if (m_timer >= 1.0f)
	{
		//	�~�߂�
		Stop();
		return;
	}

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		m_particleVel[i].x *= 0.99f;
		m_particleVel[i].z *= 0.99f;

		//	���W�X�V
		m_particlePos[i] += m_particleVel[i];
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void JumpParticle::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = GetUserResources()->GetCommonStates();

	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	���ʕ`��(�������d�����Ȃ��Ă��܂�)
	context->RSSetState(states->CullNone());

	
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	SimpleMath::Matrix world = sca * trans;

	// �s�����̂ݕ`�悷��ݒ� 
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->SetReferenceAlpha(0);
	//	���_�ɐݒ�
	m_batchEffect->SetWorld(world);
	//	view�̐ݒ�
	m_batchEffect->SetView(view);
	//	Proj�̐ݒ�
	m_batchEffect->SetProjection(proj);
	//	�摜�̐ݒ�
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	// ������������`�� 
	m_batch->Begin();
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		// ���_���i�|���S���̒��_�j 
		VertexPositionTexture vertex[4];

		//	���W
		for (int j = 0; j < 4; j++)
		{
			//	�ꖇ�ڂɒ萔������
			vertex[j] = VERTICES[j];

			vertex[j].position.x += m_particlePos[i].x;
			vertex[j].position.y += m_particlePos[i].y;
			vertex[j].position.z += m_particlePos[i].z;
		}

		m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	}
	m_batch->End();
}

/// <summary>
/// �I��
/// </summary>
void JumpParticle::Finalize()
{

}

/// <summary>
/// �p�[�e�B�N���̎��s
/// </summary>
/// <param name="pos">���W</param>
void JumpParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	�A�N�e�B�u��Ԃɂ���
	SetActive(true);
	//	���W�̐ݒ�
	SetPos(pos);

	//	�^�C�}�[��0�ɂ���
	m_timer = 0.0f;

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	���W��ݒ�
		m_particlePos[i] = SimpleMath::Vector3::Zero;

		//	�p�x
		float radian = XM_2PI / static_cast<float>(PARTICLE_NUMBER);

		//	�x�N�g��
		m_particleVel[i].x = 2.0f * cosf(radian * i);
		m_particleVel[i].y = 1.0f;
		m_particleVel[i].z = 2.0f * sinf(radian * i);

		//	�x�N�g���̐��K��
		m_particleVel[i].Normalize();
		m_particleVel[i] *= 0.05f;
	}
}

/// <summary>
/// �p�[�e�B�N���̒�~
/// </summary>
void JumpParticle::Stop()
{
	//	��A�N�e�B�u��Ԃɂ���
	SetActive(false);
}