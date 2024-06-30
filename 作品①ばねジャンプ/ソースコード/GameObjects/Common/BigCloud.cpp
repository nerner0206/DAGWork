//--------------------------------------------------------------------------------------
// File: BigCloud.h
//
// �傫���_�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BigCloud.h"

#include "MyLib/IScene.h"
#include "MyLib/BinaryFile.h"

#include <iomanip>

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[���N���X�̃|�C���^</param>
BigCloud::BigCloud(IScene* scene) :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One),
	m_nowScene(scene)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BigCloud::~BigCloud()
{

}

/// <summary>
/// ������
/// </summary>
void BigCloud::Initialize(const DirectX::SimpleMath::Vector3& pos, const float& sca)
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	
	// �G�t�F�N�g�t�@�N�g���[�̍쐬
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	���f���̍쐬
	m_model = Model::CreateFromCMO(device, DataPath::BIG_CLOUD_MODEL_PATH, *fx);

	//	�V�F�[�_�[�쐬
	CreateShader();

	//	���W�̐ݒ�
	SetPos(pos);
	//	�g�嗦�̐ݒ�
	SetSca(SimpleMath::Vector3::One * sca);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void BigCloud::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R���e�L�X�g�̎擾
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	���ʃX�e�[�g�̎擾
	auto states = GetUserResources()->GetCommonStates();
	//	�X�e�b�v�^�C�}�[�̎擾
	auto stepTimer = GetUserResources()->GetStepTimer();
	
	//	���C�g�̍��W
	SimpleMath::Vector3 lightPosition = m_nowScene->GetLightPos();
	//	���C�g�̖ڕW���W
	SimpleMath::Vector3 lightTarget = m_nowScene->GetLightTarget();
	//	���C�g�̕����x�N�g��
	SimpleMath::Vector3 lightDir = lightTarget - lightPosition;

	//	���[���h���W�̌v�Z
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	�T�C�Y���|����
	world *= SimpleMath::Matrix::CreateScale(GetSca());
	//	��]���|����
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	���W���|����
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	���f���̕`��
	m_model->Draw(context, *states, world, view, proj, false, [&]()
		{
			// �萔�o�b�t�@���X�V
			D3D11_MAPPED_SUBRESOURCE mappedResource;

			// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
			context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

			// �萔�o�b�t�@���X�V
			ConstantBuffer cb = {};
			cb.LightViewProj = SimpleMath::Matrix::Identity;
			cb.LightPos = SimpleMath::Vector4(lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);
			cb.LightDir = SimpleMath::Vector4(lightDir.x, lightDir.y, lightDir.z, stepTimer->GetTotalSeconds() / 10.0f);

			*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;

			// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
			context->Unmap(m_constantBuffer.Get(), 0);

			// �s�N�Z���V�F�[�_�g�p����萔�o�b�t�@��ݒ�
			ID3D11Buffer* cbuf_ps[] = { m_constantBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cbuf_ps);
			context->PSSetConstantBuffers(1, 1, cbuf_ps);	// �X���b�g�O��DirectXTK���g�p���Ă���̂ŃX���b�g�P���g�p����

			//	���ʕ`��(�������d�����Ȃ��Ă��܂�)
			context->RSSetState(states->CullNone());

			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
		});
}

/// <summary>
/// �I��
/// </summary>
void BigCloud::Finalize()
{
	//	�|�C���^��nullptr
	m_nowScene = nullptr;

	//	���f���̃��Z�b�g
	m_model.reset();
}

/// <summary>
/// �V�F�[�_�̍쐬
/// </summary>
void BigCloud::CreateShader()
{
	//	�f�o�C�X�̎擾
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	//	�f�[�^�̓ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(DataPath::BIG_CLOUD_VS_PATH);
	BinaryFile PSData = BinaryFile::LoadFile(DataPath::BIG_CLOUD_PS_PATH);

	//	���_�V�F�[�_�쐬
	if (FAILED(
		device->CreateVertexShader(VSData.GetData(),VSData.GetSize(),NULL,m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//	�G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	//	�s�N�Z���V�F�[�_�쐬
	if (FAILED(
		device->CreatePixelShader(PSData.GetData(),PSData.GetSize(),NULL,m_pixelShader.ReleaseAndGetAddressOf())))
	{
		//	�G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));
}