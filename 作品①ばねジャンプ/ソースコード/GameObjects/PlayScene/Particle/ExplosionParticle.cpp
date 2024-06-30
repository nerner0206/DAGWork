//--------------------------------------------------------------------------------------
// File: ExplosionParticle.cpp
//
// 爆発パーティクルクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ExplosionParticle.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  頂点の初期位置とテクスチャUVの定数
const VertexPositionTexture ExplosionParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.5f, 0.5f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f, 0.5f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.5f, -0.5f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.5f, -0.5f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

//	拡大率
const float ExplosionParticle::MAX_SCALE = 3.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cam">カメラクラスのポインタ</param>
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
/// デストラクタ
/// </summary>
ExplosionParticle::~ExplosionParticle()
{

}

/// <summary>
/// 初期化
/// </summary>
void ExplosionParticle::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();

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
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void ExplosionParticle::Update(const float& elapsedTime)
{
	//	タイマーを増加
	m_timer += elapsedTime;

	//	画像の変更
	m_texNum = GetUserResources()->Lerp(0, DataPath::EXPLOSION_PARTICLE_IMAGE_NUM, m_timer);
	if (m_texNum >= DataPath::EXPLOSION_PARTICLE_IMAGE_NUM) m_texNum = DataPath::EXPLOSION_PARTICLE_IMAGE_NUM - 1;

	//	1秒後停止
	if (m_timer >= 1.0f)
	{
		//	止める
		Stop();
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ExplosionParticle::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	// テクスチャサンプラーの設定（クランプテクスチャアドレッシングモード） 
	ID3D11SamplerState* samplers[1] = { states->PointWrap() };
	context->PSSetSamplers(0, 1, samplers);

	// 深度バッファに書き込み参照する 
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	両面描画(処理が重たくなってしまう)
	context->RSSetState(states->CullNone());

	SimpleMath::Matrix world = SimpleMath::Matrix::CreateScale(GetSca());
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

	// 不透明のみ描画する設定 
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_batchEffect->SetReferenceAlpha(0);
	//	原点に設定
	m_batchEffect->SetWorld(world);
	//	viewの設定
	m_batchEffect->SetView(view);
	//	Projの設定
	m_batchEffect->SetProjection(proj);
	//	画像の設定
	m_batchEffect->SetTexture(m_textures[m_texNum].Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	// 描画 
	m_batch->Begin();
	m_batch->DrawQuad(VERTICES[0], VERTICES[1], VERTICES[2], VERTICES[3]);
	m_batch->End();
}

/// <summary>
/// 終了
/// </summary>
void ExplosionParticle::Finalize()
{

}

/// <summary>
/// パーティクルの実行
/// </summary>
/// <param name="pos">座標</param>
void ExplosionParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	爆発音の再生
	GetAudioResources()->PlayExplosionSE();

	//	アクティブ状態にする
	SetActive(true);
	//	座標の設定
	SetPos(pos);

	//	タイマーを0にする
	m_timer = 0.0f;
	//	画像番号
	m_texNum = 0;
}

/// <summary>
/// パーティクルの停止
/// </summary>
void ExplosionParticle::Stop()
{
	//	非アクティブ状態にする
	SetActive(false);
}