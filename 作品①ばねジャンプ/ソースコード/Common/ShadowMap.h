//--------------------------------------------------------------------------------------
// File: ShadowMap.h
//
// シャドウマップクラス
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

	// シャドウマップの解像度
	static const UINT DEFALT_RESOLUTION = 1024;

	// ガウシアンフィルタの強度値
	static const float DEFALT_DISPERSION_SQ;

	// 深度バイアス（初期値 0.1 バイアス値の計算は m_offset / ライトの影響範囲）
	static const float DEFALT_OFFSET;

	// シャドウマップ作成時のニアークリップの値
	static const float NEAR_CLIP;

	// カスケードの最大数
	static const UINT MAX_CASCADES = 3;

	// カスケードの数
	UINT m_cascadeLevels;

	// カスケードの範囲
	float m_cascadeRangeTable[MAX_CASCADES];

	// csoの場所
	wchar_t m_path[MAX_PATH];

	// シャドウマップの解像度
	UINT m_resolution;

	// ガウシアンフィルタ
	bool m_gaussianFilterEnable;

	// 分散シャドウ
	bool m_vsmFilterEnable;
	
	// カスケードを色表示する場合はtrue
	bool m_visualizeCascades;

	// 深度オフセット
	float m_offset;

	// 頂点シェーダーのデータ
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_ShadowMap;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_ShadowModel;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_GausPass1;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob_GausPass2;

	// ピクセルシェーダーのデータ
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowMap;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowModel_Tex;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_ShadowModel_NoTex;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_GausPass1;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob_GausPass2;

	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_ShadowMap;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_ShadowModel;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_GausPass1;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS_GausPass2;

	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowMap;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowModel_Tex;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_ShadowModel_NoTex;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_GausPass1;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_GausPass2;

	//----- カスケードシャドウ用（↓） -----//

	// 深度バッファ用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedDepathTexture;

	// 深度ステンシルビュー
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cascadedShadowMapDSV;

	// ビューポート
	D3D11_VIEWPORT m_viewPort;

	//----- カスケードシャドウ用（↑） -----//

	//----- VSM（↓） -----//

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedShadowMapVarianceTextureArray;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cascadedShadowMapVarianceRTVArrayAll[MAX_CASCADES];
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapVarianceSRVArrayAll[MAX_CASCADES];
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapVarianceSRVArraySingle;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_temporaryShadowDepthBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_temporaryShadowDepthBufferDSV;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cascadedShadowMapTempBlurTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cascadedShadowMapTempBlurRTV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cascadedShadowMapTempBlurSRV;

	// ガウシアンフィルター用サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samShadowPoint;

	// シャドウマップ用の入力レイアの入力レイアウトウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_shadowMapInputLayout;

	// ガウシアンフィルタ
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_gaussianInputLayout;

	// 定数バッファの構造体の定義（シャドウマップ作成用）
	struct ConstantBuffer_1
	{
		DirectX::XMMATRIX LightViewProjClop;
	};

	// 定数バッファの構造体の定義（影の落ちるモデルの描画用）
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

	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowMapConstantBuffer;

	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowModelConstantBuffer;

	// サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBufferGF;

	// 定数バッファ（ガウシアンフィルタ作成用）
	struct CBufGauss
	{
		float weights[8];
		float offsetX;
		float offsetY;
		float w;
		float h;
	};

	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_gaussianConstantBuffer;

	// ガウシアンフィルタの強度用ウエイト値
	float m_weights[8];
	
	// カスケードシャドウ用クロップ行列
	DirectX::SimpleMath::Matrix m_matShadowProj[MAX_CASCADES];

private:

	// csoの入っているディレクトの設定関数
	void SetDirectory(const wchar_t* path);

	// パス付きの名前に変換する関数
	wchar_t* GetFullName(const wchar_t* name)
	{
		static wchar_t fullName[MAX_PATH];

		wcscpy_s(fullName, m_path);
		wcscat_s(fullName, name);

		return fullName;
	}

	// シャドウマップ用テクスチャにガウシアンフィルタをかける関数
	void GaussianFilter(ID3D11DeviceContext* context, const DirectX::CommonStates& states);
	
	// 上方向ベクトルを算出する関数
	DirectX::SimpleMath::Vector3 CalcUpVector(const DirectX::SimpleMath::Vector3& v);

	// クロップ行列を作成する関数
	DirectX::SimpleMath::Matrix CreateClopMatrix(
		const DirectX::SimpleMath::Matrix& lightViewProj,
		const DirectX::SimpleMath::Vector3& cameraPos,
		const DirectX::SimpleMath::Vector3& cameraTargetPos
		, float nearClip, float farClip);

public:

	// コンストラクタ
	ShadowMap();

	// 初期化関数
	void Initialize(ID3D11Device* device, const float* cascadeRangeTbl, UINT cascadeLevels, const wchar_t* path = nullptr, UINT resolution = DEFALT_RESOLUTION, bool filterEnable = false);

	// シャドウマップの作成
	void CreateShadowMap(ID3D11DeviceContext* context, const DirectX::CommonStates& states,
		DirectX::SimpleMath::Vector3 lightPos, DirectX::SimpleMath::Vector3 lightTargetPos, float lightRange,
		DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 cameraTargetPos, std::function<void()> setDrawShadowModel);

	// シャドウマップ作成時に呼び出すカスタムステート
	void DrawShadowMap(ID3D11DeviceContext* context);

	// 影付きのモデルを描画したい時に呼び出すカスタムステート
	// テクスチャなしのモデルを表示したい場合は第２引数をfalseにする事
	void DrawShadow(ID3D11DeviceContext* context, bool texture = true);

	// シャドウマップ用テクスチャリソースを取得する関数（デバッグ用）
	ID3D11ShaderResourceView* GetShadowMapTexture(int cascadeLevel)
	{
		return m_cascadedShadowMapVarianceSRVArrayAll[cascadeLevel].Get();
	}

	// ガウシアンフィルタ用ウエイト値を計算して設定する関数
	// 0に近づくほど影はくっきりになる。 値が大きいほどぼける。
	// ※初期値は3.0で設定しています。
	void ComputeGaussianFilterWeights(float dispersion_sq);

	// 深度バッファの比較オフセット値の設定（ぼかした場合はオフセット値は無効）
	void SetOffset(float offset)
	{
		m_offset = offset;
	}

	// カスケードを色分け表示を設定する関数
	void VisualizeCascades(bool flag)
	{
		m_visualizeCascades = flag;
	}

	// カスケード範囲テーブルの設定関数
	void SetCascadeRange(const float* table, UINT size)
	{
		if (size >= MAX_CASCADES) size = MAX_CASCADES;
		for (UINT i = 0; i < size; i++)
		{
			m_cascadeRangeTable[i] = table[i];
		}
	}

	// カスケードの枚数を取得する関数
	UINT GetCascadeLevel()
	{
		return m_cascadeLevels;
	}
};

