//--------------------------------------------------------------------------------------
// File: ConfettiParticle.cpp
//
// ������p�[�e�B�N���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ConfettiParticle.h"

#include <WICTextureLoader.h> 
#include <random>

using namespace DirectX;

//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
const VertexPositionTexture ConfettiParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.05f, 0.05f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.05f, 0.05f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.05f, -0.05f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.05f, -0.05f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

//	���W�̏���l
const float ConfettiParticle::MAX_POSITION = 10.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cam">�J�����N���X�̃|�C���^</param>
ConfettiParticle::ConfettiParticle() :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ConfettiParticle::~ConfettiParticle()
{

}

/// <summary>
/// ������
/// </summary>
void ConfettiParticle::Initialize()
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
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	// �e�N�X�`���̃��[�h 
	CreateWICTextureFromFile(
		device,
		DataPath::FADE_WHITE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf());

	//	�p�[�e�B�N���̐�������������
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	���W�̒ǉ�
		m_particlePos.push_back(SimpleMath::Vector3::Zero);
		//	���x�̒ǉ�
		m_particleVel_Y.push_back(0.0f);
		//	�F�̒ǉ�
		m_particleColor.push_back(SimpleMath::Vector4::Zero);
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void ConfettiParticle::Update(const float& elapsedTime)
{
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	���W�X�V
		m_particlePos[i].y += m_particleVel_Y[i];

		//	���W���Œፂ�x�ȉ�
		if (m_particlePos[i].y <= -MAX_POSITION)
		{
			//	���W�̃��Z�b�g
			m_particlePos[i].y = MAX_POSITION;
		}
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void ConfettiParticle::Render(
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

	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale(GetSca());
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

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
		VertexPositionColorTexture vertex[4];

		//	���W
		for (int j = 0; j < 4; j++)
		{
			//	�ꖇ�ڂɒ萔������
			vertex[j].position = VERTICES[j].position;
			vertex[j].textureCoordinate = VERTICES[j].textureCoordinate;
			vertex[j].color = m_particleColor[i];

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
void ConfettiParticle::Finalize()
{

}

/// <summary>
/// �p�[�e�B�N���̎��s
/// </summary>
/// <param name="pos">���W</param>
void ConfettiParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	�A�N�e�B�u��Ԃɂ���
	SetActive(true);
	//	���W�̐ݒ�
	SetPos(pos);

	//	�����̏�����
	std::random_device seed;
	std::default_random_engine engine(seed());
	//	�F�̗����͈�
	std::uniform_real_distribution<> colorDist(0, 1.0f);
	//	�ʒu�̕�
	std::uniform_real_distribution<> posDist(-MAX_POSITION, MAX_POSITION);
	//	���x�̗����͈�
	std::uniform_real_distribution<> velDist(-0.1f, -0.05f);

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	0�`1�̗����̎擾
		float pos_x = static_cast<float>(posDist(engine));
		float pos_z = static_cast<float>(posDist(engine));

		//	�F�̗����̎擾
		float r = static_cast<float>(colorDist(engine));
		float g = static_cast<float>(colorDist(engine));
		float b = static_cast<float>(colorDist(engine));

		//	���x�̗����̎擾
		m_particleVel_Y[i] = static_cast<float>(velDist(engine));

		//	���W�̐ݒ�
		m_particlePos[i] = SimpleMath::Vector3(pos_x, MAX_POSITION, pos_z);
		//	�F�̐ݒ�
		m_particleColor[i] = SimpleMath::Vector4(r, g, b, 1.0f);
	}

	//	�N���b�J�[���̍Đ�
	GetAudioResources()->PlayCracker01SE();
	GetAudioResources()->PlayCracker02SE();
}

/// <summary>
/// �p�[�e�B�N���̒�~
/// </summary>
void ConfettiParticle::Stop()
{
	//	��A�N�e�B�u��Ԃɂ���
	SetActive(false);
}