//--------------------------------------------------------------------------------------
// File: WindParticle.cpp
//
// ���p�[�e�B�N���N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "WindParticle.h"

#include "GameObjects/PlayScene/StageObjects/Wind.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
const VertexPositionTexture WindParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="wind">���N���X�̃|�C���^</param>
WindParticle::WindParticle(Wind* wind) :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One),
	m_timer(0.0f),
	m_wind(wind)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WindParticle::~WindParticle()
{

}

/// <summary>
/// ������
/// </summary>
void WindParticle::Initialize()
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
		DataPath::WIND_PARTICLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);

	//	�͂̌����̎擾
	SimpleMath::Vector3 forward = m_wind->GetVector();

	//	��������
	SimpleMath::Vector3 vertical = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_wind->GetRotQua());
	//	��������
	SimpleMath::Vector3 horizontal = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX, m_wind->GetRotQua());

	SimpleMath::Vector3 offPos = (-vertical * m_wind->GetSca().y * 0.5f) + (-horizontal * m_wind->GetSca().x * 0.5f);

	//	�p�[�e�B�N���̐�������������
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		float x = i % 4;
		float y = i / 4;

		//	���W
		SimpleMath::Vector3 pos = offPos + (horizontal * m_wind->GetSca().x * 0.25f * x) + (vertical * m_wind->GetSca().y * 0.25f * y);
		SimpleMath::Vector3 startPos = pos + (-forward * m_wind->GetSca().z * 0.5f);

		//	�J�n���W�̒ǉ�
		m_particleStartPos.push_back(startPos);

		//	���W�̒ǉ�
		if(((i / 4) % 2 == 0 && i % 2 == 0) || ((i / 4) % 2 == 1 && i % 2 == 1)) m_particlePos.push_back(pos); 
		else m_particlePos.push_back(startPos);
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void WindParticle::Update(const float& elapsedTime)
{
	//	�^�C�}�[�𑝉�
	m_timer += elapsedTime;

	//	�͂̌����̎擾
	SimpleMath::Vector3 forward = m_wind->GetVector();

	//	��������
	SimpleMath::Vector3 vertical = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_wind->GetRotQua());
	//	��������
	SimpleMath::Vector3 horizontal = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX, m_wind->GetRotQua());

	//	�p�[�e�B�N���̐�������������
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	�ړ�������
		m_particlePos[i] += (forward * m_wind->GetPower() * elapsedTime);
		//	�J�n�ʒu�Ƃ̋����v�Z
		float l = (m_particleStartPos[i] - m_particlePos[i]).Length();
		//	�g�嗦���傫���ꍇ�߂�
		if (l > m_wind->GetSca().z) m_particlePos[i] = m_particleStartPos[i];
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
/// <param name="camera">�J�����N���X�̃|�C���^</param>
void WindParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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

	SimpleMath::Matrix world = SimpleMath::Matrix::CreateTranslation(m_wind->GetPos());

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

	//	���X�ɓ����ɂ���
	m_batchEffect->SetAlpha(0.5f);

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
void WindParticle::Finalize()
{

}

/// <summary>
/// �p�[�e�B�N���̎��s
/// </summary>
/// <param name="pos">���W</param>
void WindParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	�A�N�e�B�u��Ԃɂ���
	SetActive(true);
	//	���W�̐ݒ�
	SetPos(pos);

	//	�^�C�}�[��0�ɂ���
	m_timer = 0.0f;
}

/// <summary>
/// �p�[�e�B�N���̒�~
/// </summary>
void WindParticle::Stop()
{
	//	��A�N�e�B�u��Ԃɂ���
	SetActive(false);
}