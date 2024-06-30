//--------------------------------------------------------------------------------------
// File: ShadowMap.cpp
//
// �V���h�E�}�b�v�N���X
//
// Date: 2022.7.3
// Author: Hideyasu Imase
//
// Ver2.0 �J�X�P�[�h�V���h�E�ɑΉ�
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ShadowMap.h"
#include "VertexTypes.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �K�E�V�A���t�B���^�̋��x�l
const float ShadowMap::DEFALT_DISPERSION_SQ = 3.0f;

// �[�x�o�C�A�X�i�����l 0.1 �o�C�A�X�l�̌v�Z�� m_offset / ���C�g�̉e���͈́j
const float ShadowMap::DEFALT_OFFSET = 0.1f;

// �V���h�E�}�b�v�쐬���̃j�A�[�N���b�v�̒l
const float ShadowMap::NEAR_CLIP = 0.1f;

ShadowMap::ShadowMap()
	: m_gaussianFilterEnable(true)
	, m_vsmFilterEnable(true)
	, m_resolution(ShadowMap::DEFALT_RESOLUTION)
	, m_viewPort{}
	, m_offset(ShadowMap::DEFALT_OFFSET)
	, m_weights{}
	, m_cascadeLevels(MAX_CASCADES)
	, m_cascadeRangeTable{}
	, m_matShadowProj{}
	, m_visualizeCascades(false)
{
}

// �������֐�
void ShadowMap::Initialize(ID3D11Device* device, const float* cascadeRangeTbl, UINT cascadeLevels, const wchar_t* path, UINT resolution, bool filterEnable)
{
	SetDirectory(path);

	// �J�X�P�[�h�͈̔͂̐ݒ�
	SetCascadeRange(cascadeRangeTbl, cascadeLevels);

	// �K�E�V�A���t�B���^�̐ݒ�
	m_gaussianFilterEnable = filterEnable;

	// ���U�V���h�E
	m_vsmFilterEnable = filterEnable;

	// �V���h�E�}�b�v�̉𑜓x
	m_resolution = resolution;

	// �J�X�P�[�h�̐�
	if(cascadeLevels >= 1 && cascadeLevels <= MAX_CASCADES) m_cascadeLevels = cascadeLevels;

	// ���_�V�F�[�_�[�̓ǂݍ���
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_VS_Depth.cso"), m_vsBlob_ShadowMap.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_VS.cso"), m_vsBlob_ShadowModel.GetAddressOf()));
	if (m_gaussianFilterEnable)
	{
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_VS_PASS1.cso"), m_vsBlob_GausPass1.GetAddressOf()));
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_VS_PASS2.cso"), m_vsBlob_GausPass2.GetAddressOf()));
	}

	// �s�N�Z���V�F�[�_�[�̓ǂݍ���
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_Depth.cso"), m_psBlob_ShadowMap.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_Texture.cso"), m_psBlob_ShadowModel_Tex.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_NoneTex.cso"), m_psBlob_ShadowModel_NoTex.GetAddressOf()));
	if (m_gaussianFilterEnable)
	{
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_PS_PASS1.cso"), m_psBlob_GausPass1.GetAddressOf()));
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_PS_PASS2.cso"), m_psBlob_GausPass2.GetAddressOf()));
	}

	// ���_�V�F�[�_�[�̍쐬
	device->CreateVertexShader(m_vsBlob_ShadowMap->GetBufferPointer(), m_vsBlob_ShadowMap->GetBufferSize(), nullptr, m_VS_ShadowMap.GetAddressOf());
	device->CreateVertexShader(m_vsBlob_ShadowModel->GetBufferPointer(), m_vsBlob_ShadowModel->GetBufferSize(), nullptr, m_VS_ShadowModel.GetAddressOf());
	if (m_gaussianFilterEnable)
	{
		device->CreateVertexShader(m_vsBlob_GausPass1->GetBufferPointer(), m_vsBlob_GausPass1->GetBufferSize(), nullptr, m_VS_GausPass1.GetAddressOf());
		device->CreateVertexShader(m_vsBlob_GausPass2->GetBufferPointer(), m_vsBlob_GausPass2->GetBufferSize(), nullptr, m_VS_GausPass2.GetAddressOf());
	}

	// �s�N�Z���V�F�[�_�[�̍쐬
	device->CreatePixelShader(m_psBlob_ShadowMap->GetBufferPointer(), m_psBlob_ShadowMap->GetBufferSize(), nullptr, m_PS_ShadowMap.GetAddressOf());
	device->CreatePixelShader(m_psBlob_ShadowModel_Tex->GetBufferPointer(), m_psBlob_ShadowModel_Tex->GetBufferSize(), nullptr, m_PS_ShadowModel_Tex.GetAddressOf());
	device->CreatePixelShader(m_psBlob_ShadowModel_NoTex->GetBufferPointer(), m_psBlob_ShadowModel_NoTex->GetBufferSize(), nullptr, m_PS_ShadowModel_NoTex.GetAddressOf());
	if (m_gaussianFilterEnable)
	{
		device->CreatePixelShader(m_psBlob_GausPass1->GetBufferPointer(), m_psBlob_GausPass1->GetBufferSize(), nullptr, m_PS_GausPass1.GetAddressOf());
		device->CreatePixelShader(m_psBlob_GausPass2->GetBufferPointer(), m_psBlob_GausPass2->GetBufferSize(), nullptr, m_PS_GausPass2.GetAddressOf());
	}

	// ���̓��C�A�E�g�̍쐬
	DX::ThrowIfFailed(
		device->CreateInputLayout(
			VertexPositionNormalTangentColorTexture::InputElements, VertexPositionNormalTangentColorTexture::InputElementCount,
			m_vsBlob_ShadowModel->GetBufferPointer(), m_vsBlob_ShadowModel->GetBufferSize(),
			m_shadowMapInputLayout.GetAddressOf()
		)
	);

	if (m_gaussianFilterEnable)
	{
		// ���̓��C�A�E�g�̍쐬
		DX::ThrowIfFailed(
			device->CreateInputLayout(
				VertexPositionTexture::InputElements, VertexPositionTexture::InputElementCount,
				m_vsBlob_GausPass1->GetBufferPointer(), m_vsBlob_GausPass1->GetBufferSize(),
				m_gaussianInputLayout.GetAddressOf()
			)
		);
	}

	//----- �J�X�P�[�h�V���h�E�p�i���j -----//

	{
		// �e�N�X�`���̍쐬
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_resolution;   // ��
		desc.Height = m_resolution;  // ����
		desc.MipLevels = 1;       // �~�b�v�}�b�v ���x����
		desc.ArraySize = 1;       // �z��T�C�Y
		desc.Format = DXGI_FORMAT_R32_TYPELESS;  // �t�H�[�}�b�g
		desc.SampleDesc.Count = 1;  // �}���`�T���v�����O�̐ݒ�
		desc.SampleDesc.Quality = 0;  // �}���`�T���v�����O�̕i��
		desc.Usage = D3D11_USAGE_DEFAULT;      // �f�t�H���g�g�p�@
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �[�x/�X�e���V���Ƃ��Ďg�p
		desc.CPUAccessFlags = 0;   // CPU����̓A�N�Z�X���Ȃ�
		desc.MiscFlags = 0;   // ���̑��̐ݒ�Ȃ�
		// �[�x�������ݗp
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedDepathTexture.GetAddressOf()));
	}

	{
		// �[�x/�X�e���V�� �r���[�̍쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Flags = 0;
		DX::ThrowIfFailed(device->CreateDepthStencilView(m_cascadedDepathTexture.Get(), &desc, m_cascadedShadowMapDSV.GetAddressOf()));
	}

	// �r���[�|�[�g
	m_viewPort.Height = static_cast<FLOAT>(m_resolution);
	m_viewPort.Width = static_cast<FLOAT>(m_resolution);
	m_viewPort.MaxDepth = 1.0f;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;

	//----- �J�X�P�[�h�V���h�E�p�i���j -----//

	//----- VSM�p�i���j -----//
	{
		// �e�N�X�`���̍쐬�i�V���h�E�}�b�v�쐬�p�j
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_resolution;   // ��
		desc.Height = m_resolution;  // ����
		desc.MipLevels = 1;       // �~�b�v�}�b�v ���x����
		desc.ArraySize = m_cascadeLevels;       // �z��T�C�Y
		desc.Format = DXGI_FORMAT_R16G16_FLOAT;  // �t�H�[�}�b�g
		desc.SampleDesc.Count = 1;  // �}���`�T���v�����O�̐ݒ�
		desc.SampleDesc.Quality = 0;  // �}���`�T���v�����O�̕i��
		desc.Usage = D3D11_USAGE_DEFAULT;      // �f�t�H���g�g�p�@
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;   // CPU����̓A�N�Z�X���Ȃ�
		desc.MiscFlags = 0;   // ���̑��̐ݒ�Ȃ�
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedShadowMapVarianceTextureArray.GetAddressOf()));

		desc.ArraySize = 1;       // �z��T�C�Y
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedShadowMapTempBlurTexture.GetAddressOf()));

		// �e�N�X�`���̍쐬�i�[�x�o�b�t�@�p�j
		desc.Format = DXGI_FORMAT_R32_TYPELESS;  // �t�H�[�}�b�g
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_temporaryShadowDepthBufferTexture.GetAddressOf()));
	}

	{
		// �[�x/�X�e���V�� �r���[�̍쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Flags = 0;
		desc.Texture2D.MipSlice = 0;
		DX::ThrowIfFailed(device->CreateDepthStencilView(m_temporaryShadowDepthBufferTexture.Get(),
			&desc, m_temporaryShadowDepthBufferDSV.GetAddressOf()));
	}

	{
		// �����_�[�^�[�Q�b�g�r���[�̍쐬
		D3D11_RENDER_TARGET_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_R16G16_FLOAT;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2D.MipSlice = 0;
		for (UINT i = 0; i < m_cascadeLevels; i++)
		{
			desc.Texture2DArray.FirstArraySlice = i;
			desc.Texture2DArray.ArraySize = 1;
			DX::ThrowIfFailed(device->CreateRenderTargetView(m_cascadedShadowMapVarianceTextureArray.Get(),
				&desc, m_cascadedShadowMapVarianceRTVArrayAll[i].GetAddressOf()));
		}

		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;
		DX::ThrowIfFailed(device->CreateRenderTargetView(m_cascadedShadowMapTempBlurTexture.Get(),
			&desc, m_cascadedShadowMapTempBlurRTV.GetAddressOf()));
	}

	{
		// �V�F�[�_ ���\�[�X �r���[�̍쐬
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_R16G16_FLOAT; // �t�H�[�}�b�g
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;  // 2D�e�N�X�`��
		desc.Texture2DArray.ArraySize = 1;
		desc.Texture2DArray.MostDetailedMip = 0;   // �ŏ��̃~�b�v�}�b�v ���x��
		desc.Texture2DArray.MipLevels = 1;
		for (UINT i = 0; i < m_cascadeLevels; i++)
		{
			desc.Texture2DArray.FirstArraySlice = i;
			DX::ThrowIfFailed(device->CreateShaderResourceView(m_cascadedShadowMapVarianceTextureArray.Get(),
				&desc, m_cascadedShadowMapVarianceSRVArrayAll[i].GetAddressOf()));
		}
		desc.Texture2DArray.FirstArraySlice = 0;
		desc.Texture2DArray.ArraySize = m_cascadeLevels;
		DX::ThrowIfFailed(device->CreateShaderResourceView(m_cascadedShadowMapVarianceTextureArray.Get(),
			&desc, m_cascadedShadowMapVarianceSRVArraySingle.GetAddressOf()));

		desc.Texture2DArray.ArraySize = 1;
		desc.Texture2DArray.FirstArraySlice = 0;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.MostDetailedMip = 0;
		DX::ThrowIfFailed(device->CreateShaderResourceView(m_cascadedShadowMapTempBlurTexture.Get(),
			&desc, m_cascadedShadowMapTempBlurSRV.GetAddressOf()));
	}

	{
		// �K�E�V�A���t�B���^�[�p�T���v���[�̍쐬
		D3D11_SAMPLER_DESC desc;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 0;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = 0;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.BorderColor[0] = 0.0f;
		desc.BorderColor[1] = 0.0f;
		desc.BorderColor[2] = 0.0f;
		desc.BorderColor[3] = 0.0f;
		DX::ThrowIfFailed(device->CreateSamplerState(&desc, m_samShadowPoint.GetAddressOf()));
	}

	// �萔�o�b�t�@�̍쐬
	{
		D3D11_BUFFER_DESC desc = {};
		// �o�b�t�@�T�C�Y�͂P�U�̔{���łȂ��Ƃ����Ȃ�
		size_t size = sizeof(ConstantBuffer_1);
		if (size % 16) size++;
		desc.ByteWidth = static_cast<UINT>(size * 16);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, m_shadowMapConstantBuffer.GetAddressOf()));
	}

	// �萔�o�b�t�@�̍쐬
	{
		D3D11_BUFFER_DESC desc = {};
		// �o�b�t�@�T�C�Y�͂P�U�̔{���łȂ��Ƃ����Ȃ�
		size_t size = sizeof(ConstantBuffer_2);
		if (size % 16) size++;
		desc.ByteWidth = static_cast<UINT>(size * 16);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, m_shadowModelConstantBuffer.GetAddressOf()));
	}

	{
		// VSM�p�T���v���[�̍쐬
		D3D11_SAMPLER_DESC desc;
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 1;		// �ٕ����t�B���^�����O�͏������ׂ��l���Ė����ɂ��Ă���
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0;
		desc.MaxLOD = 0;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.BorderColor[0] = 0.0f;
		desc.BorderColor[1] = 0.0f;
		desc.BorderColor[2] = 0.0f;
		desc.BorderColor[3] = 0.0f;

		DX::ThrowIfFailed(device->CreateSamplerState(&desc, m_sampler.GetAddressOf()));
	}

	if (m_gaussianFilterEnable)
	{
		// ���_�o�b�t�@
		D3D11_BUFFER_DESC desc = {};

		VertexPositionTexture vertex[4] =
		{
			VertexPositionTexture(Vector3(-1.0f,  1.0f, 0.0f), Vector2(0.0f, 0.0f)),
			VertexPositionTexture(Vector3(1.0f,  1.0f, 0.0f), Vector2(1.0f, 0.0f)),
			VertexPositionTexture(Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f)),
			VertexPositionTexture(Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f)),
		};

		desc.ByteWidth = (UINT)(sizeof(VertexPositionTexture) * 4);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA subData;
		subData.pSysMem = vertex;
		subData.SysMemPitch = 0;
		subData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(device->CreateBuffer(&desc, &subData, m_vertexBufferGF.GetAddressOf()));
	}

	// �萔�o�b�t�@�̍쐬
	if (m_gaussianFilterEnable)
	{
		D3D11_BUFFER_DESC desc = {};
		// �o�b�t�@�T�C�Y�͂P�U�̔{���łȂ��Ƃ����Ȃ�
		size_t size = sizeof(CBufGauss);
		if (size % 16) size++;
		desc.ByteWidth = static_cast<UINT>(size * 16);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, m_gaussianConstantBuffer.GetAddressOf()));
	}

	if (m_gaussianFilterEnable)
	{
		// �K�E�V�A���t�B���^�̃E�G�C�g�l���v�Z���Đݒ肷��
		ComputeGaussianFilterWeights(DEFALT_DISPERSION_SQ);
	}

}

void ShadowMap::CreateShadowMap(
	ID3D11DeviceContext* context,
	const DirectX::CommonStates& states,
	DirectX::SimpleMath::Vector3 lightPos,
	DirectX::SimpleMath::Vector3 targetPos,
	float lightRange,
	DirectX::SimpleMath::Vector3 cameraPos,
	DirectX::SimpleMath::Vector3 cameraTargetPos,
	std::function<void()> setDrawShadowModel
)
{
	Vector3 vec = targetPos - lightPos;
	Matrix lightView = Matrix::CreateLookAt(lightPos, targetPos, CalcUpVector(vec));
	Matrix lightProj = Matrix::CreateOrthographicOffCenter(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, lightRange);
	Matrix lightViewProj = lightView * lightProj;

	// �f�o�C�X�R���e�L�X�g�̃N���A
	context->ClearState();

	for (size_t i = 0; i < m_cascadeLevels; i++)
	{
		// �[�x�o�b�t�@���N���A
		context->ClearDepthStencilView(m_temporaryShadowDepthBufferDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		context->ClearRenderTargetView(m_cascadedShadowMapVarianceRTVArrayAll[i].Get(), Colors::White);
		// �����_�[�^�[�Q�b�g��ݒ�
		context->OMSetRenderTargets(1, m_cascadedShadowMapVarianceRTVArrayAll[i].GetAddressOf(), m_temporaryShadowDepthBufferDSV.Get());

		// �N���b�v�s����쐬
		m_matShadowProj[i] = lightProj * CreateClopMatrix(lightViewProj, cameraPos, cameraTargetPos, 0.0f, m_cascadeRangeTable[i]);

		// �r���[�|�[�g�̐ݒ�
		context->RSSetViewports(1, &m_viewPort);

		//----------------------------------//
		// �萔�o�b�t�@��ݒ�               //
		//----------------------------------//
		{
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			DX::ThrowIfFailed(
				context->Map(m_shadowMapConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)
			);

			ConstantBuffer_1 buffer;
	
			buffer.LightViewProjClop = XMMatrixTranspose(lightView * m_matShadowProj[i]);

			*static_cast<ConstantBuffer_1*>(mappedResource.pData) = buffer;

			context->Unmap(m_shadowMapConstantBuffer.Get(), 0);
		}
		//----------------------------------//
		// �萔�o�b�t�@��ݒ�i�I�j         //
		//----------------------------------//

		// �e���f���̕`��
		if (setDrawShadowModel)
		{
			setDrawShadowModel();
		}
	}

	//----------------------------------//
	// �萔�o�b�t�@��ݒ�               //
	//----------------------------------//
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DX::ThrowIfFailed(
			context->Map(m_shadowModelConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)
		);

		// ���K���f�o�C�X���W�n����X�N���[�����W�n�֕ϊ�����s��
		Matrix matTextureScale = Matrix::CreateScale(0.5f, -0.5f, 1.0f);
		Matrix matTextureTrans = Matrix::CreateTranslation(0.5f, 0.5f, 0.0f);

		ConstantBuffer_2 buffer;

		buffer.LightView = XMMatrixTranspose(lightView);
		buffer.LightViewProj = XMMatrixTranspose(lightViewProj);
		for (UINT i = 0; i < m_cascadeLevels; i++)
		{
			Matrix mShadowTexture = m_matShadowProj[i] * matTextureScale * matTextureTrans;
			buffer.CascadeScale[i].x = mShadowTexture.m[0][0];
			buffer.CascadeScale[i].y = mShadowTexture.m[1][1];
			buffer.CascadeScale[i].z = mShadowTexture.m[2][2];
			buffer.CascadeScale[i].w = 1.0f;
			buffer.CascadeOffset[i].x = mShadowTexture.m[3][0];
			buffer.CascadeOffset[i].y = mShadowTexture.m[3][1];
			buffer.CascadeOffset[i].z = mShadowTexture.m[3][2];
			buffer.CascadeOffset[i].w = 0.0f;
		}
		buffer.lightPosition = lightPos;
		buffer.maxDepth = lightRange;
		buffer.offset = m_offset / lightRange;
		buffer.VSMFilterEnable = m_vsmFilterEnable;
		buffer.minBorderPadding = 1.0f / static_cast<float>(m_resolution);
		buffer.maxBorderPadding = (static_cast<float>(m_resolution) - 1.0f) / static_cast<float>(m_resolution);
		buffer.CascadeLevels = m_cascadeLevels;
		buffer.VisualizeCascades = static_cast<int>(m_visualizeCascades);

		*static_cast<ConstantBuffer_2*>(mappedResource.pData) = buffer;
		context->Unmap(m_shadowModelConstantBuffer.Get(), 0);
	}
	//----------------------------------//
	// �萔�o�b�t�@��ݒ�i�I�j         //
	//----------------------------------//

	if (m_gaussianFilterEnable)
	{
		// �V���h�E�}�b�v���ڂ���
		GaussianFilter(context, states);
	}
}

void ShadowMap::DrawShadowMap(ID3D11DeviceContext* context)
{
	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_shadowMapInputLayout.Get());

	// ���_�V�F�[�_�[�̐ݒ�
	context->VSSetShader(m_VS_ShadowMap.Get(), nullptr, 0);
	context->VSSetConstantBuffers(1, 1, m_shadowMapConstantBuffer.GetAddressOf());

	// �s�N�Z���V�F�[�_�[�̐ݒ�
	context->PSSetShader(m_PS_ShadowMap.Get(), nullptr, 0);
}

void ShadowMap::DrawShadow(ID3D11DeviceContext* context, bool texture)
{
	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_shadowMapInputLayout.Get());

	// ���_�V�F�[�_�[�̐ݒ�
	context->VSSetShader(m_VS_ShadowModel.Get(), nullptr, 0);
	context->VSSetConstantBuffers(1, 1, m_shadowModelConstantBuffer.GetAddressOf());

	// �s�N�Z���V�F�[�_�[�̐ݒ�
	if (texture)
	{
		context->PSSetShader(m_PS_ShadowModel_Tex.Get(), nullptr, 0);
	}
	else
	{
		context->PSSetShader(m_PS_ShadowModel_NoTex.Get(), nullptr, 0);
	}
	context->PSSetConstantBuffers(1, 1, m_shadowModelConstantBuffer.GetAddressOf());
	context->PSSetSamplers(1, 1, m_sampler.GetAddressOf());
	context->PSSetShaderResources(1, 1, m_cascadedShadowMapVarianceSRVArraySingle.GetAddressOf());
}

void ShadowMap::SetDirectory(const wchar_t* path)
{
	if (path && *path != 0)
	{
		wcscpy_s(m_path, path);
		size_t len = wcsnlen(m_path, MAX_PATH);
		if (len > 0 && len < (MAX_PATH - 1))
		{
			// Ensure it has a trailing slash
			if (m_path[len - 1] != L'\\')
			{
				m_path[len] = L'\\';
				m_path[len + 1] = 0;
			}
		}
	}
	else
	{
		*m_path = 0;
	}
}

void ShadowMap::GaussianFilter(ID3D11DeviceContext* context, const DirectX::CommonStates& states)
{
	//----------------------------------//
	// �萔�o�b�t�@��ݒ�               //
	//----------------------------------//
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DX::ThrowIfFailed(
			context->Map(m_gaussianConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)
		);

		CBufGauss buffer;
		memcpy(buffer.weights, m_weights, sizeof(float) * 8);
		buffer.offsetX = 16.0f / m_resolution;
		buffer.offsetY = 16.0f / m_resolution;
		buffer.w = static_cast<float>(m_resolution);
		buffer.h = static_cast<float>(m_resolution);

		*static_cast<CBufGauss*>(mappedResource.pData) = buffer;
		context->Unmap(m_gaussianConstantBuffer.Get(), 0);
	}

	//----------------------------------//
	// �萔�o�b�t�@��ݒ�i�I�j         //
	//----------------------------------//

	// �f�o�C�X�R���e�L�X�g�̃N���A
	context->ClearState();

	// �v���~�e�B�u�̎�ނ�ݒ肷��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_gaussianInputLayout.Get());

	// �r���[�|�[�g�̐ݒ�
	context->RSSetViewports(1, &m_viewPort);

	// �J�����O���[�h�̐ݒ�
	context->RSSetState(states.CullNone());

	// �u�����h�X�e�[�g�̐ݒ�
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�̐ݒ�
	context->OMSetDepthStencilState(states.DepthNone(), 0);

	ID3D11ShaderResourceView* srvNull = nullptr;
	ID3D11DepthStencilView* dsNullview = nullptr;

	for (size_t i = 0; i < m_cascadeLevels; i++)
	{
		context->PSSetShaderResources(0, 1, &srvNull);

		// �����_�[�^�[�Q�b�g��ݒ�
		context->OMSetRenderTargets(1, m_cascadedShadowMapTempBlurRTV.GetAddressOf(), dsNullview);

		// ���_�V�F�[�_�[�̐ݒ�
		context->VSSetShader(m_VS_GausPass1.Get(), nullptr, 0);
		context->VSSetConstantBuffers(0, 1, m_gaussianConstantBuffer.GetAddressOf());

		// �s�N�Z���V�F�[�_�[�̐ݒ�
		context->PSSetShader(m_PS_GausPass1.Get(), nullptr, 0);
		context->PSSetConstantBuffers(0, 1, m_gaussianConstantBuffer.GetAddressOf());
		context->PSSetShaderResources(0, 1, m_cascadedShadowMapVarianceSRVArrayAll[i].GetAddressOf());

		// �T���v���[�̐ݒ�
		ID3D11SamplerState* samplers[] = { m_samShadowPoint.Get() };
		context->PSSetSamplers(0, 1, samplers);

		// ���_�o�b�t�@��ݒ肷��
		{
			auto vertexBuffer = m_vertexBufferGF.Get();
			UINT vertexStride = sizeof(VertexPositionTexture);
			UINT vertexOffset = 0;

			context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
		}

		// �`��i�c�ɂڂ������摜�j
		context->Draw(4, 0);

		context->PSSetShaderResources(0, 1, &srvNull);

		// �����_�[�^�[�Q�b�g��ݒ�
		context->OMSetRenderTargets(1, m_cascadedShadowMapVarianceRTVArrayAll[i].GetAddressOf(), dsNullview);

		// ���_�V�F�[�_�[�̐ݒ�
		context->VSSetShader(m_VS_GausPass2.Get(), nullptr, 0);

		// �s�N�Z���V�F�[�_�[�̐ݒ�
		context->PSSetShader(m_PS_GausPass2.Get(), nullptr, 0);

		// �c�ɂڂ������摜���V�F�[�_�[�֓n��
		context->PSSetShaderResources(0, 1, m_cascadedShadowMapTempBlurSRV.GetAddressOf());

		// �`��i���ɂڂ������摜�j
		context->Draw(4, 0);
	}
}

DirectX::SimpleMath::Vector3 ShadowMap::CalcUpVector(const DirectX::SimpleMath::Vector3& v)
{
	Matrix rotY = Matrix::CreateRotationY(atan2f(v.z, v.x));
	Vector3 tmp = Vector3::Transform(v, rotY);
	Vector3 up = Vector3(-tmp.y, tmp.x, tmp.z);
	up = Vector3::Transform(up, rotY.Invert());
	up.Normalize();
	return up;
}

DirectX::SimpleMath::Matrix ShadowMap::CreateClopMatrix(const DirectX::SimpleMath::Matrix& lightViewProj, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraTargetPos, float nearClip, float farClip)
{
	// �G���A�����鎋����̂W���_�����߂�
	float nearY = tanf(XMConvertToRadians(45.0f * 0.5f)) * nearClip;
	float nearX = nearY;
	float farY = tanf(XMConvertToRadians(45.0f * 0.5f)) * farClip;
	float farX = farY;
	Vector3 cameraForward = cameraTargetPos - cameraPos;
	cameraForward.Normalize();
	Vector3 nearPos = cameraPos + cameraForward * nearClip;
	Vector3 farPos = cameraPos + cameraForward * farClip;

	Vector3 v[8];
	v[0] = nearPos + Vector3(nearX, nearY, 0.0f);
	v[1] = nearPos + Vector3(-nearX, nearY, 0.0f);
	v[2] = nearPos + Vector3(nearX, -nearY, 0.0f);
	v[3] = nearPos + Vector3(-nearX, -nearY, 0.0f);
	v[4] = farPos + Vector3(farX, farY, 0.0f);
	v[5] = farPos + Vector3(-farX, farY, 0.0f);
	v[6] = farPos + Vector3(farX, -farY, 0.0f);
	v[7] = farPos + Vector3(-farX, -farY, 0.0f);

	Vector3 vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	Vector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };

	for (size_t j = 0; j < 8; j++)
	{
		Vector3::Transform(v[j], lightViewProj);
		vMax = Vector3::Max(vMax, v[j]);
		vMin = Vector3::Min(vMin, v[j]);
	}

	float xScale = 2.0f / (vMax.x - vMin.x);
	float yScale = 2.0f / (vMax.y - vMin.y);
	float xOffset = (vMax.x + vMin.x) * -0.5f * xScale;
	float yOffset = (vMax.y + vMin.y) * -0.5f * yScale;

	Matrix clop;
	clop.m[0][0] = xScale;
	clop.m[1][1] = yScale;
	clop.m[3][0] = xOffset;
	clop.m[3][1] = yOffset;

	return clop;
}

void ShadowMap::ComputeGaussianFilterWeights(float dispersion_sq)
{
	// 0��ݒ肳�ꂽ�ꍇ�̑Ή���0.01�𑫂��Ă���
	float dispersion = dispersion_sq * dispersion_sq + 0.01f;
	float total = 0.0f;
	const int NUM_WEIGHT = 8;

	for (int i = 0; i < NUM_WEIGHT; ++i)
	{
		float pos = 1.0f + 2.0f * (float)i;
		m_weights[i] = expf(-0.5f * (pos * pos) / dispersion);
		total += 2.0f * m_weights[i];
	}

	float invTotal = 1.0f / total;
	for (int i = 0; i < NUM_WEIGHT; ++i)
	{
		m_weights[i] *= invTotal;
	}
}

