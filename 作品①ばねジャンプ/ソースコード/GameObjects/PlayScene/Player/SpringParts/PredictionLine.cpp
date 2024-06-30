//--------------------------------------------------------------------------------------
// File: PredictionLine.cpp
//
// �\�����N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PredictionLine.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

const float PredictionLine::PREDICTION_TIME = 3.0f;

//  ���_�̏����ʒu�ƃe�N�X�`��UV�̒萔
const VertexPositionTexture PredictionLine::VERTICES[4] =
{
	VertexPositionTexture(SimpleMath::Vector3(-0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
PredictionLine::PredictionLine() :
	m_isActive(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PredictionLine::~PredictionLine()
{

}

/// <summary>
/// ������
/// </summary>
void PredictionLine::Initialize()
{
	//	���[�U�[���\�[�X�̎擾
	UserResources* ur = UserResources::GetInstance();

	//	�f�o�C�X�̎擾
	auto device = ur->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	auto context = ur->GetDeviceResources()->GetD3DDeviceContext();

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
		DataPath::RED_CIRCLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PredictionLine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	���[�U�[���\�[�X�̎擾
	UserResources* ur = UserResources::GetInstance();

	//	�R���e�L�X�g�̎擾
	auto context = ur->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�N���X�̎擾
	auto states = ur->GetCommonStates();

	// �e�N�X�`���T���v���[�̐ݒ�i�N�����v�e�N�X�`���A�h���b�V���O���[�h�j 
	ID3D11SamplerState* samplers[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��� 
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	���ʕ`��(�������d�����Ȃ��Ă��܂�)
	context->RSSetState(states->CullNone());

	// �s�����̂ݕ`�悷��ݒ� 
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->SetReferenceAlpha(0);
	//	���_�ɐݒ�
	m_batchEffect->SetWorld(SimpleMath::Matrix::Identity);
	//	view�̐ݒ�
	m_batchEffect->SetView(view);
	//	Proj�̐ݒ�
	m_batchEffect->SetProjection(proj);
	//	�摜�̐ݒ�
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	//	������
	m_batchEffect->SetAlpha(0.5f);

	// ������������`�� 
	m_batch->Begin();

	//	���W�̐������`��
	for (SimpleMath::Vector3 pos : m_poses)
	{
		// ���_���i�|���S���̒��_�j 
		VertexPositionTexture vertex[8];

		//	���W�v�Z
		for (int i = 0; i < 4; i++)
		{
			//	�ꖇ�ڂɒ萔������
			vertex[i] = VERTICES[i];
			//	�񖇖ڂɂ������萔������
			vertex[i + 4] = VERTICES[i];
			//	�񖇖ڂ̂����W�𔽓]������
			vertex[i + 4].position.z *= -1;

			vertex[i].position.x += pos.x;
			vertex[i].position.y += pos.y;
			vertex[i].position.z += pos.z;
			vertex[i + 4].position.x += pos.x;
			vertex[i + 4].position.y += pos.y;
			vertex[i + 4].position.z += pos.z;
		}

		//	�̕`��
		m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
		m_batch->DrawQuad(vertex[4], vertex[5], vertex[6], vertex[7]);
	}

	m_batch->End();
}

/// <summary>
/// �I��
/// </summary>
void PredictionLine::Finalize()
{
	m_inputLayout.Reset();
	m_texture.Reset();
	m_batchEffect.reset();
	m_batch.reset();
}

/// <summary>
/// ���Z�b�g
/// </summary>
void PredictionLine::Reset()
{
	//	���W�̃��Z�b�g
	m_poses.clear();
}