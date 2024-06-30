//--------------------------------------------------------------------------------------
// File: ShadowMap.cpp
//
// シャドウマップクラス
//
// Date: 2022.7.3
// Author: Hideyasu Imase
//
// Ver2.0 カスケードシャドウに対応
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ShadowMap.h"
#include "VertexTypes.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ガウシアンフィルタの強度値
const float ShadowMap::DEFALT_DISPERSION_SQ = 3.0f;

// 深度バイアス（初期値 0.1 バイアス値の計算は m_offset / ライトの影響範囲）
const float ShadowMap::DEFALT_OFFSET = 0.1f;

// シャドウマップ作成時のニアークリップの値
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

// 初期化関数
void ShadowMap::Initialize(ID3D11Device* device, const float* cascadeRangeTbl, UINT cascadeLevels, const wchar_t* path, UINT resolution, bool filterEnable)
{
	SetDirectory(path);

	// カスケードの範囲の設定
	SetCascadeRange(cascadeRangeTbl, cascadeLevels);

	// ガウシアンフィルタの設定
	m_gaussianFilterEnable = filterEnable;

	// 分散シャドウ
	m_vsmFilterEnable = filterEnable;

	// シャドウマップの解像度
	m_resolution = resolution;

	// カスケードの数
	if(cascadeLevels >= 1 && cascadeLevels <= MAX_CASCADES) m_cascadeLevels = cascadeLevels;

	// 頂点シェーダーの読み込み
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_VS_Depth.cso"), m_vsBlob_ShadowMap.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_VS.cso"), m_vsBlob_ShadowModel.GetAddressOf()));
	if (m_gaussianFilterEnable)
	{
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_VS_PASS1.cso"), m_vsBlob_GausPass1.GetAddressOf()));
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_VS_PASS2.cso"), m_vsBlob_GausPass2.GetAddressOf()));
	}

	// ピクセルシェーダーの読み込み
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_Depth.cso"), m_psBlob_ShadowMap.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_Texture.cso"), m_psBlob_ShadowModel_Tex.GetAddressOf()));
	DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"SM_PS_NoneTex.cso"), m_psBlob_ShadowModel_NoTex.GetAddressOf()));
	if (m_gaussianFilterEnable)
	{
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_PS_PASS1.cso"), m_psBlob_GausPass1.GetAddressOf()));
		DX::ThrowIfFailed(D3DReadFileToBlob(GetFullName(L"GF_PS_PASS2.cso"), m_psBlob_GausPass2.GetAddressOf()));
	}

	// 頂点シェーダーの作成
	device->CreateVertexShader(m_vsBlob_ShadowMap->GetBufferPointer(), m_vsBlob_ShadowMap->GetBufferSize(), nullptr, m_VS_ShadowMap.GetAddressOf());
	device->CreateVertexShader(m_vsBlob_ShadowModel->GetBufferPointer(), m_vsBlob_ShadowModel->GetBufferSize(), nullptr, m_VS_ShadowModel.GetAddressOf());
	if (m_gaussianFilterEnable)
	{
		device->CreateVertexShader(m_vsBlob_GausPass1->GetBufferPointer(), m_vsBlob_GausPass1->GetBufferSize(), nullptr, m_VS_GausPass1.GetAddressOf());
		device->CreateVertexShader(m_vsBlob_GausPass2->GetBufferPointer(), m_vsBlob_GausPass2->GetBufferSize(), nullptr, m_VS_GausPass2.GetAddressOf());
	}

	// ピクセルシェーダーの作成
	device->CreatePixelShader(m_psBlob_ShadowMap->GetBufferPointer(), m_psBlob_ShadowMap->GetBufferSize(), nullptr, m_PS_ShadowMap.GetAddressOf());
	device->CreatePixelShader(m_psBlob_ShadowModel_Tex->GetBufferPointer(), m_psBlob_ShadowModel_Tex->GetBufferSize(), nullptr, m_PS_ShadowModel_Tex.GetAddressOf());
	device->CreatePixelShader(m_psBlob_ShadowModel_NoTex->GetBufferPointer(), m_psBlob_ShadowModel_NoTex->GetBufferSize(), nullptr, m_PS_ShadowModel_NoTex.GetAddressOf());
	if (m_gaussianFilterEnable)
	{
		device->CreatePixelShader(m_psBlob_GausPass1->GetBufferPointer(), m_psBlob_GausPass1->GetBufferSize(), nullptr, m_PS_GausPass1.GetAddressOf());
		device->CreatePixelShader(m_psBlob_GausPass2->GetBufferPointer(), m_psBlob_GausPass2->GetBufferSize(), nullptr, m_PS_GausPass2.GetAddressOf());
	}

	// 入力レイアウトの作成
	DX::ThrowIfFailed(
		device->CreateInputLayout(
			VertexPositionNormalTangentColorTexture::InputElements, VertexPositionNormalTangentColorTexture::InputElementCount,
			m_vsBlob_ShadowModel->GetBufferPointer(), m_vsBlob_ShadowModel->GetBufferSize(),
			m_shadowMapInputLayout.GetAddressOf()
		)
	);

	if (m_gaussianFilterEnable)
	{
		// 入力レイアウトの作成
		DX::ThrowIfFailed(
			device->CreateInputLayout(
				VertexPositionTexture::InputElements, VertexPositionTexture::InputElementCount,
				m_vsBlob_GausPass1->GetBufferPointer(), m_vsBlob_GausPass1->GetBufferSize(),
				m_gaussianInputLayout.GetAddressOf()
			)
		);
	}

	//----- カスケードシャドウ用（↓） -----//

	{
		// テクスチャの作成
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_resolution;   // 幅
		desc.Height = m_resolution;  // 高さ
		desc.MipLevels = 1;       // ミップマップ レベル数
		desc.ArraySize = 1;       // 配列サイズ
		desc.Format = DXGI_FORMAT_R32_TYPELESS;  // フォーマット
		desc.SampleDesc.Count = 1;  // マルチサンプリングの設定
		desc.SampleDesc.Quality = 0;  // マルチサンプリングの品質
		desc.Usage = D3D11_USAGE_DEFAULT;      // デフォルト使用法
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 深度/ステンシルとして使用
		desc.CPUAccessFlags = 0;   // CPUからはアクセスしない
		desc.MiscFlags = 0;   // その他の設定なし
		// 深度書き込み用
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedDepathTexture.GetAddressOf()));
	}

	{
		// 深度/ステンシル ビューの作成
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Flags = 0;
		DX::ThrowIfFailed(device->CreateDepthStencilView(m_cascadedDepathTexture.Get(), &desc, m_cascadedShadowMapDSV.GetAddressOf()));
	}

	// ビューポート
	m_viewPort.Height = static_cast<FLOAT>(m_resolution);
	m_viewPort.Width = static_cast<FLOAT>(m_resolution);
	m_viewPort.MaxDepth = 1.0f;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;

	//----- カスケードシャドウ用（↑） -----//

	//----- VSM用（↓） -----//
	{
		// テクスチャの作成（シャドウマップ作成用）
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_resolution;   // 幅
		desc.Height = m_resolution;  // 高さ
		desc.MipLevels = 1;       // ミップマップ レベル数
		desc.ArraySize = m_cascadeLevels;       // 配列サイズ
		desc.Format = DXGI_FORMAT_R16G16_FLOAT;  // フォーマット
		desc.SampleDesc.Count = 1;  // マルチサンプリングの設定
		desc.SampleDesc.Quality = 0;  // マルチサンプリングの品質
		desc.Usage = D3D11_USAGE_DEFAULT;      // デフォルト使用法
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;   // CPUからはアクセスしない
		desc.MiscFlags = 0;   // その他の設定なし
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedShadowMapVarianceTextureArray.GetAddressOf()));

		desc.ArraySize = 1;       // 配列サイズ
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_cascadedShadowMapTempBlurTexture.GetAddressOf()));

		// テクスチャの作成（深度バッファ用）
		desc.Format = DXGI_FORMAT_R32_TYPELESS;  // フォーマット
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr, m_temporaryShadowDepthBufferTexture.GetAddressOf()));
	}

	{
		// 深度/ステンシル ビューの作成
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Flags = 0;
		desc.Texture2D.MipSlice = 0;
		DX::ThrowIfFailed(device->CreateDepthStencilView(m_temporaryShadowDepthBufferTexture.Get(),
			&desc, m_temporaryShadowDepthBufferDSV.GetAddressOf()));
	}

	{
		// レンダーターゲットビューの作成
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
		// シェーダ リソース ビューの作成
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_R16G16_FLOAT; // フォーマット
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;  // 2Dテクスチャ
		desc.Texture2DArray.ArraySize = 1;
		desc.Texture2DArray.MostDetailedMip = 0;   // 最初のミップマップ レベル
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
		// ガウシアンフィルター用サンプラーの作成
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

	// 定数バッファの作成
	{
		D3D11_BUFFER_DESC desc = {};
		// バッファサイズは１６の倍数でないといけない
		size_t size = sizeof(ConstantBuffer_1);
		if (size % 16) size++;
		desc.ByteWidth = static_cast<UINT>(size * 16);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, m_shadowMapConstantBuffer.GetAddressOf()));
	}

	// 定数バッファの作成
	{
		D3D11_BUFFER_DESC desc = {};
		// バッファサイズは１６の倍数でないといけない
		size_t size = sizeof(ConstantBuffer_2);
		if (size % 16) size++;
		desc.ByteWidth = static_cast<UINT>(size * 16);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(device->CreateBuffer(&desc, nullptr, m_shadowModelConstantBuffer.GetAddressOf()));
	}

	{
		// VSM用サンプラーの作成
		D3D11_SAMPLER_DESC desc;
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 1;		// 異方性フィルタリングは処理負荷を考えて無効にしている
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
		// 頂点バッファ
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

	// 定数バッファの作成
	if (m_gaussianFilterEnable)
	{
		D3D11_BUFFER_DESC desc = {};
		// バッファサイズは１６の倍数でないといけない
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
		// ガウシアンフィルタのウエイト値を計算して設定する
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

	// デバイスコンテキストのクリア
	context->ClearState();

	for (size_t i = 0; i < m_cascadeLevels; i++)
	{
		// 深度バッファをクリア
		context->ClearDepthStencilView(m_temporaryShadowDepthBufferDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		context->ClearRenderTargetView(m_cascadedShadowMapVarianceRTVArrayAll[i].Get(), Colors::White);
		// レンダーターゲットを設定
		context->OMSetRenderTargets(1, m_cascadedShadowMapVarianceRTVArrayAll[i].GetAddressOf(), m_temporaryShadowDepthBufferDSV.Get());

		// クロップ行列を作成
		m_matShadowProj[i] = lightProj * CreateClopMatrix(lightViewProj, cameraPos, cameraTargetPos, 0.0f, m_cascadeRangeTable[i]);

		// ビューポートの設定
		context->RSSetViewports(1, &m_viewPort);

		//----------------------------------//
		// 定数バッファを設定               //
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
		// 定数バッファを設定（終）         //
		//----------------------------------//

		// 影モデルの描画
		if (setDrawShadowModel)
		{
			setDrawShadowModel();
		}
	}

	//----------------------------------//
	// 定数バッファを設定               //
	//----------------------------------//
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DX::ThrowIfFailed(
			context->Map(m_shadowModelConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)
		);

		// 正規化デバイス座標系からスクリーン座標系へ変換する行列
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
	// 定数バッファを設定（終）         //
	//----------------------------------//

	if (m_gaussianFilterEnable)
	{
		// シャドウマップをぼかす
		GaussianFilter(context, states);
	}
}

void ShadowMap::DrawShadowMap(ID3D11DeviceContext* context)
{
	// 入力レイアウトの設定
	context->IASetInputLayout(m_shadowMapInputLayout.Get());

	// 頂点シェーダーの設定
	context->VSSetShader(m_VS_ShadowMap.Get(), nullptr, 0);
	context->VSSetConstantBuffers(1, 1, m_shadowMapConstantBuffer.GetAddressOf());

	// ピクセルシェーダーの設定
	context->PSSetShader(m_PS_ShadowMap.Get(), nullptr, 0);
}

void ShadowMap::DrawShadow(ID3D11DeviceContext* context, bool texture)
{
	// 入力レイアウトの設定
	context->IASetInputLayout(m_shadowMapInputLayout.Get());

	// 頂点シェーダーの設定
	context->VSSetShader(m_VS_ShadowModel.Get(), nullptr, 0);
	context->VSSetConstantBuffers(1, 1, m_shadowModelConstantBuffer.GetAddressOf());

	// ピクセルシェーダーの設定
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
	// 定数バッファを設定               //
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
	// 定数バッファを設定（終）         //
	//----------------------------------//

	// デバイスコンテキストのクリア
	context->ClearState();

	// プリミティブの種類を設定する
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 入力レイアウトの設定
	context->IASetInputLayout(m_gaussianInputLayout.Get());

	// ビューポートの設定
	context->RSSetViewports(1, &m_viewPort);

	// カリングモードの設定
	context->RSSetState(states.CullNone());

	// ブレンドステートの設定
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);

	// 深度バッファの設定
	context->OMSetDepthStencilState(states.DepthNone(), 0);

	ID3D11ShaderResourceView* srvNull = nullptr;
	ID3D11DepthStencilView* dsNullview = nullptr;

	for (size_t i = 0; i < m_cascadeLevels; i++)
	{
		context->PSSetShaderResources(0, 1, &srvNull);

		// レンダーターゲットを設定
		context->OMSetRenderTargets(1, m_cascadedShadowMapTempBlurRTV.GetAddressOf(), dsNullview);

		// 頂点シェーダーの設定
		context->VSSetShader(m_VS_GausPass1.Get(), nullptr, 0);
		context->VSSetConstantBuffers(0, 1, m_gaussianConstantBuffer.GetAddressOf());

		// ピクセルシェーダーの設定
		context->PSSetShader(m_PS_GausPass1.Get(), nullptr, 0);
		context->PSSetConstantBuffers(0, 1, m_gaussianConstantBuffer.GetAddressOf());
		context->PSSetShaderResources(0, 1, m_cascadedShadowMapVarianceSRVArrayAll[i].GetAddressOf());

		// サンプラーの設定
		ID3D11SamplerState* samplers[] = { m_samShadowPoint.Get() };
		context->PSSetSamplers(0, 1, samplers);

		// 頂点バッファを設定する
		{
			auto vertexBuffer = m_vertexBufferGF.Get();
			UINT vertexStride = sizeof(VertexPositionTexture);
			UINT vertexOffset = 0;

			context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);
		}

		// 描画（縦にぼかした画像）
		context->Draw(4, 0);

		context->PSSetShaderResources(0, 1, &srvNull);

		// レンダーターゲットを設定
		context->OMSetRenderTargets(1, m_cascadedShadowMapVarianceRTVArrayAll[i].GetAddressOf(), dsNullview);

		// 頂点シェーダーの設定
		context->VSSetShader(m_VS_GausPass2.Get(), nullptr, 0);

		// ピクセルシェーダーの設定
		context->PSSetShader(m_PS_GausPass2.Get(), nullptr, 0);

		// 縦にぼかした画像をシェーダーへ渡す
		context->PSSetShaderResources(0, 1, m_cascadedShadowMapTempBlurSRV.GetAddressOf());

		// 描画（横にぼかした画像）
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
	// エリアを内包する視錘台の８頂点を求める
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
	// 0を設定された場合の対応で0.01を足している
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

