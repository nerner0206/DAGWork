//--------------------------------------------------------------------------------------
// File: ShadowMap.h
//
// �V���h�E�}�b�v�N���X
//
// Date: 2022.6.19
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <d3dcompiler.h>
#include "SimpleMath.h"
#include "CommonStates.h"

class ShadowMap
{
private:

	// �V���h�E�}�b�v�̉𑜓x
	static const UINT DEFALT_RESOLUTION = 1024;

	// �K�E�V�A���t�B���^�̋��x�l
	static const float DEFALT_DISPERSION_SQ;

	// �[�x�o�C�A�X�i�����l 0.1 �o�C�A�X�l�̌v�Z�� m_offset / ���C�g�̉e���͈́j
	static const float DEFALT_OFFSET;

	// �V���h�E�}�b�v�쐬���̃j�A�[�N���b�v�̒l
	static const float NEAR_CLIP;

	// �J�X�P�[�h�̍ő吔
	static const UINT MAX_CASCADES = 3;

	// �J�X�P�[�h�̐�
	UINT m_cascadeLevels;

	// �J�X�P�[�h�͈̔�
	float m_cascadeRangeTable[MAX_CASCADES];

	// cso�̏ꏊ
	wchar_t m_path[MAX_PATH];

	// �V���h�E�}�b�v�̉𑜓x
	UINT m_resolution;

	// �K�E�V�A���t�B���^
	bool m_gaussianFilterEnable;

	// ���U�V���h�E
	bool m_vsmFilterEnable;
	
	// �J�X�P�[�h��F�\������ꍇ��true
	bool m_visualizeCascades;

	// �[�x�I�t�Z�b�g
	float m_offset;

	// ���_�V�F�[�_�[�̃f�[�^
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_ShadowMap;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_ShadowModel;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_GausPass1;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_GausPass2;

	// �s�N�Z���V�F�[�_�[�̃f�[�^
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowMap;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowModel_Tex;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowModel_NoTex;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_GausPass1;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_GausPass2;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_ShadowMap;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_ShadowModel;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_GausPass1;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_GausPass2;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowMap;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowModel_Tex;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowModel_NoTex;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_GausPass1;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_GausPass2;

	//----- �J�X�P�[�h�V���h�E�p�i���j -----//

	// �[�x�o�b�t�@�p�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedDepathTexture;

	// �[�x�X�e���V���r���[
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cascadedShadowMapDSV;

	// �r���[�|�[�g
	D3D11_VIEWPORT m_viewPort;

	//----- �J�X�P�[�h�V���h�E�p�i���j -----//

	//----- VSM�i���j -----//

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedShadowMapVarianceTextureArray;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cascadedShadowMapVarianceRTVArrayAll[MAX_CASCADES];
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapVarianceSRVArrayAll[MAX_CASCADES];
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapVarianceSRVArraySingle;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_temporaryShadowDepthBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_temporaryShadowDepthBufferDSV;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedShadowMapTempBlurTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cascadedShadowMapTempBlurRTV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapTempBlurSRV;

	// �K�E�V�A���t�B���^�[�p�T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samShadowPoint;

	// �V���h�E�}�b�v�p�̓��̓��C�A�̓��̓��C�A�E�g�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_shadowMapInputLayout;

	// �K�E�V�A���t�B���^
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_gaussianInputLayout;

	// �萔�o�b�t�@�̍\���̂̒�`�i�V���h�E�}�b�v�쐬�p�j
	struct ConstantBuffer_1
	{
		DirectX::XMMATRIX LightViewProjClop;
	};

	// �萔�o�b�t�@�̍\���̂̒�`�i�e�̗����郂�f���̕`��p�j
	struct ConstantBuffer_2
	{
		DirectX::XMMATRIX LightView;
		DirectX::XMMATRIX LightViewProj;
		DirectX::XMFLOAT4 CascadeOffset[MAX_CASCADES];
		DirectX::XMFLOAT4 CascadeScale[MAX_CASCADES];
		DirectX::XMFLOAT3 lightPosition;
		float maxDepth;
		float offset;
		int VSMFilterEnable;
		float minBorderPadding;
		float maxBorderPadding;
		int CascadeLevels;
		int VisualizeCascades;
	};

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowMapConstantBuffer;

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowModelConstantBuffer;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBufferGF;

	// �萔�o�b�t�@�i�K�E�V�A���t�B���^�쐬�p�j
	struct CBufGauss
	{
		float weights[8];
		float offsetX;
		float offsetY;
		float w;
		float h;
	};

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_gaussianConstantBuffer;

	// �K�E�V�A���t�B���^�̋��x�p�E�G�C�g�l
	float m_weights[8];
	
	// �J�X�P�[�h�V���h�E�p�N���b�v�s��
	DirectX::SimpleMath::Matrix m_matShadowProj[MAX_CASCADES];

private:

	// cso�̓����Ă���f�B���N�g�̐ݒ�֐�
	void SetDirectory(const wchar_t* path);

	// �p�X�t���̖��O�ɕϊ�����֐�
	wchar_t* GetFullName(const wchar_t* name)
	{
		static wchar_t fullName[MAX_PATH];

		wcscpy_s(fullName, m_path);
		wcscat_s(fullName, name);

		return fullName;
	}

	// �V���h�E�}�b�v�p�e�N�X�`���ɃK�E�V�A���t�B���^��������֐�
	void GaussianFilter(ID3D11DeviceContext* context, const DirectX::CommonStates& states);
	
	// ������x�N�g�����Z�o����֐�
	DirectX::SimpleMath::Vector3 CalcUpVector(const DirectX::SimpleMath::Vector3& v);

	// �N���b�v�s����쐬����֐�
	DirectX::SimpleMath::Matrix CreateClopMatrix(
		const DirectX::SimpleMath::Matrix& lightViewProj,
		const DirectX::SimpleMath::Vector3& cameraPos,
		const DirectX::SimpleMath::Vector3& cameraTargetPos
		, float nearClip, float farClip);

public:

	// �R���X�g���N�^
	ShadowMap();

	// �������֐�
	void Initialize(ID3D11Device* device, const float* cascadeRangeTbl, UINT cascadeLevels, const wchar_t* path = nullptr, UINT resolution = DEFALT_RESOLUTION, bool filterEnable = false);

	// �V���h�E�}�b�v�̍쐬
	void CreateShadowMap(ID3D11DeviceContext* context, const DirectX::CommonStates& states,
		DirectX::SimpleMath::Vector3 lightPos, DirectX::SimpleMath::Vector3 lightTargetPos, float lightRange,
		DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 cameraTargetPos, std::function<void()> setDrawShadowModel);

	// �V���h�E�}�b�v�쐬���ɌĂяo���J�X�^���X�e�[�g
	void DrawShadowMap(ID3D11DeviceContext* context);

	// �e�t���̃��f����`�悵�������ɌĂяo���J�X�^���X�e�[�g
	// �e�N�X�`���Ȃ��̃��f����\���������ꍇ�͑�Q������false�ɂ��鎖
	void DrawShadow(ID3D11DeviceContext* context, bool texture = true);

	// �V���h�E�}�b�v�p�e�N�X�`�����\�[�X���擾����֐��i�f�o�b�O�p�j
	ID3D11ShaderResourceView* GetShadowMapTexture(int cascadeLevel)
	{
		return m_cascadedShadowMapVarianceSRVArrayAll[cascadeLevel].Get();
	}

	// �K�E�V�A���t�B���^�p�E�G�C�g�l���v�Z���Đݒ肷��֐�
	// 0�ɋ߂Â��قǉe�͂�������ɂȂ�B �l���傫���قǂڂ���B
	// �������l��3.0�Őݒ肵�Ă��܂��B
	void ComputeGaussianFilterWeights(float dispersion_sq);

	// �[�x�o�b�t�@�̔�r�I�t�Z�b�g�l�̐ݒ�i�ڂ������ꍇ�̓I�t�Z�b�g�l�͖����j
	void SetOffset(float offset)
	{
		m_offset = offset;
	}

	// �J�X�P�[�h��F�����\����ݒ肷��֐�
	void VisualizeCascades(bool flag)
	{
		m_visualizeCascades = flag;
	}

	// �J�X�P�[�h�͈̓e�[�u���̐ݒ�֐�
	void SetCascadeRange(const float* table, UINT size)
	{
		if (size >= MAX_CASCADES) size = MAX_CASCADES;
		for (UINT i = 0; i < size; i++)
		{
			m_cascadeRangeTable[i] = table[i];
		}
	}

	// �J�X�P�[�h�̖������擾����֐�
	UINT GetCascadeLevel()
	{
		return m_cascadeLevels;
	}
};

