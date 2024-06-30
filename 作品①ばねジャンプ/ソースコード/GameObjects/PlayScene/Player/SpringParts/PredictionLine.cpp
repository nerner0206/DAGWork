//--------------------------------------------------------------------------------------
// File: PredictionLine.cpp
//
// 予測線クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PredictionLine.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

const float PredictionLine::PREDICTION_TIME = 3.0f;

//  頂点の初期位置とテクスチャUVの定数
const VertexPositionTexture PredictionLine::VERTICES[4] =
{
	VertexPositionTexture(SimpleMath::Vector3(-0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
	VertexPositionTexture(SimpleMath::Vector3(0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
	VertexPositionTexture(SimpleMath::Vector3(-0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// コンストラクタ
/// </summary>
PredictionLine::PredictionLine() :
	m_isActive(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PredictionLine::~PredictionLine()
{

}

/// <summary>
/// 初期化
/// </summary>
void PredictionLine::Initialize()
{
	//	ユーザーリソースの取得
	UserResources* ur = UserResources::GetInstance();

	//	デバイスの取得
	auto device = ur->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	auto context = ur->GetDeviceResources()->GetD3DDeviceContext();

	// エフェクトの作成 
	m_batchEffect = std::make_unique<AlphaTestEffect>(device);
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);

	// 入力レイアウト生成 
	void const* shaderByteCode;
	size_t byteCodeLength;

	//	頂点情報
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(
		VertexPositionTexture::InputElements,
		VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()
	);

	// プリミティブバッチの作成 
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// テクスチャのロード 
	CreateWICTextureFromFile(
		device,
		DataPath::RED_CIRCLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PredictionLine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	ユーザーリソースの取得
	UserResources* ur = UserResources::GetInstance();

	//	コンテキストの取得
	auto context = ur->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = ur->GetCommonStates();

	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	両面描画(処理が重たくなってしまう)
	context->RSSetState(states->CullNone());

	// 不透明のみ描画する設定 
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->SetReferenceAlpha(0);
	//	原点に設定
	m_batchEffect->SetWorld(SimpleMath::Matrix::Identity);
	//	viewの設定
	m_batchEffect->SetView(view);
	//	Projの設定
	m_batchEffect->SetProjection(proj);
	//	画像の設定
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	//	半透明
	m_batchEffect->SetAlpha(0.5f);

	// 半透明部分を描画 
	m_batch->Begin();

	//	座標の数だけ描画
	for (SimpleMath::Vector3 pos : m_poses)
	{
		// 頂点情報（板ポリゴンの頂点） 
		VertexPositionTexture vertex[8];

		//	座標計算
		for (int i = 0; i < 4; i++)
		{
			//	一枚目に定数を入れる
			vertex[i] = VERTICES[i];
			//	二枚目にも同じ定数を入れる
			vertex[i + 4] = VERTICES[i];
			//	二枚目のｚ座標を反転させる
			vertex[i + 4].position.z *= -1;

			vertex[i].position.x += pos.x;
			vertex[i].position.y += pos.y;
			vertex[i].position.z += pos.z;
			vertex[i + 4].position.x += pos.x;
			vertex[i + 4].position.y += pos.y;
			vertex[i + 4].position.z += pos.z;
		}

		//	板の描画
		m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
		m_batch->DrawQuad(vertex[4], vertex[5], vertex[6], vertex[7]);
	}

	m_batch->End();
}

/// <summary>
/// 終了
/// </summary>
void PredictionLine::Finalize()
{
	m_inputLayout.Reset();
	m_texture.Reset();
	m_batchEffect.reset();
	m_batch.reset();
}

/// <summary>
/// リセット
/// </summary>
void PredictionLine::Reset()
{
	//	座標のリセット
	m_poses.clear();
}