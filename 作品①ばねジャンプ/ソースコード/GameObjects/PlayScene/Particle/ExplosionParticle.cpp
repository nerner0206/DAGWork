//--------------------------------------------------------------------------------------
// File: ExplosionParticle.cpp
//
// �����p�[�e�B�N���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ExplosionParticle.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
const VertexPositionTexture ExplosionParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.5f, 0.5f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f, 0.5f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f, -0.5f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.5f, -0.5f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

//	�g�嗦
const float ExplosionParticle::MAX_SCALE = 3.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cam">�J�����N���X�̃|�C���^</param>
ExplosionParticle::ExplosionParticle() :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One * MAX_SCALE),
	m_timer(0.0f),
	m_texNum(0)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ExplosionParticle::~ExplosionParticle()
{

}

/// <summary>
/// ������
/// </summary>
void ExplosionParticle::Initialize()
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
	for (int i = 0; i < DataPath::EXPLOSION_PARTICLE_IMAGE_NUM; i++)
	{
		CreateWICTextureFromFile(
			device,
			DataPath::EXPLOSION_PARTICLE_IMAGE_PATHs[i],
			nullptr,
			m_textures[i].GetAddressOf());
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void ExplosionParticle::Update(const float& elapsedTime)
{
	//	�^�C�}�[�𑝉�
	m_timer += elapsedTime;

	//	�摜�̕ύX
	m_texNum = GetUserResources()->Lerp(0, DataPath::EXPLOSION_PARTICLE_IMAGE_NUM, m_timer);
	if (m_texNum >= DataPath::EXPLOSION_PARTICLE_IMAGE_NUM) m_texNum = DataPath::EXPLOSION_PARTICLE_IMAGE_NUM - 1;

	//	1�b���~
	if (m_timer >= 1.0f)
	{
		//	�~�߂�
		Stop();
		return;
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void ExplosionParticle::Render(
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

	SimpleMath::Matrix world = SimpleMath::Matrix::CreateScale(GetSca());
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
	m_batchEffect->SetTexture(m_textures[m_texNum].Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	// �`�� 
	m_batch->Begin();
	m_batch->DrawQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
	m_batch->End();
}

/// <summary>
/// �I��
/// </summary>
void ExplosionParticle::Finalize()
{

}

/// <summary>
/// �p�[�e�B�N���̎��s
/// </summary>
/// <param name="pos">���W</param>
void ExplosionParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	�������̍Đ�
	GetAudioResources()->PlayExplosionSE();

	//	�A�N�e�B�u��Ԃɂ���
	SetActive(true);
	//	���W�̐ݒ�
	SetPos(pos);

	//	�^�C�}�[��0�ɂ���
	m_timer = 0.0f;
	//	�摜�ԍ�
	m_texNum = 0;
}

/// <summary>
/// �p�[�e�B�N���̒�~
/// </summary>
void ExplosionParticle::Stop()
{
	//	��A�N�e�B�u��Ԃɂ���
	SetActive(false);
}