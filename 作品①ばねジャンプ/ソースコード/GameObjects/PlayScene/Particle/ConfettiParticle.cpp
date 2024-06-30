//--------------------------------------------------------------------------------------
// File: ConfettiParticle.cpp
//
// 紙吹雪パーティクルクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ConfettiParticle.h"

#include <WICTextureLoader.h> 
#include <random>

using namespace DirectX;

//  頂点の初期位置とテクスチャUVの定数
const VertexPositionTexture ConfettiParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.05f, 0.05f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.05f, 0.05f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.05f, -0.05f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.05f, -0.05f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

//	座標の上限値
const float ConfettiParticle::MAX_POSITION = 10.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cam">カメラクラスのポインタ</param>
ConfettiParticle::ConfettiParticle() :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One)
{

}

/// <summary>
/// デストラクタ
/// </summary>
ConfettiParticle::~ConfettiParticle()
{

}

/// <summary>
/// 初期化
/// </summary>
void ConfettiParticle::Initialize()
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
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	// テクスチャのロード 
	CreateWICTextureFromFile(
		device,
		DataPath::FADE_WHITE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf());

	//	パーティクルの数分だけ初期化
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	座標の追加
		m_particlePos.push_back(SimpleMath::Vector3::Zero);
		//	速度の追加
		m_particleVel_Y.push_back(0.0f);
		//	色の追加
		m_particleColor.push_back(SimpleMath::Vector4::Zero);
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void ConfettiParticle::Update(const float& elapsedTime)
{
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	座標更新
		m_particlePos[i].y += m_particleVel_Y[i];

		//	座標が最低高度以下
		if (m_particlePos[i].y <= -MAX_POSITION)
		{
			//	座標のリセット
			m_particlePos[i].y = MAX_POSITION;
		}
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ConfettiParticle::Render(
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

	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale(GetSca());
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
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	// 半透明部分を描画 
	m_batch->Begin();
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		// 頂点情報（板ポリゴンの頂点） 
		VertexPositionColorTexture vertex[4];

		//	座標
		for (int j = 0; j < 4; j++)
		{
			//	一枚目に定数を入れる
			vertex[j].position = VERTICES[j].position;
			vertex[j].textureCoordinate = VERTICES[j].textureCoordinate;
			vertex[j].color = m_particleColor[i];

			vertex[j].position.x += m_particlePos[i].x;
			vertex[j].position.y += m_particlePos[i].y;
			vertex[j].position.z += m_particlePos[i].z;
		}

		m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	}
	m_batch->End();
}

/// <summary>
/// 終了
/// </summary>
void ConfettiParticle::Finalize()
{

}

/// <summary>
/// パーティクルの実行
/// </summary>
/// <param name="pos">座標</param>
void ConfettiParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	アクティブ状態にする
	SetActive(true);
	//	座標の設定
	SetPos(pos);

	//	乱数の初期化
	std::random_device seed;
	std::default_random_engine engine(seed());
	//	色の乱数範囲
	std::uniform_real_distribution<> colorDist(0, 1.0f);
	//	位置の幅
	std::uniform_real_distribution<> posDist(-MAX_POSITION, MAX_POSITION);
	//	速度の乱数範囲
	std::uniform_real_distribution<> velDist(-0.1f, -0.05f);

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	0～1の乱数の取得
		float pos_x = static_cast<float>(posDist(engine));
		float pos_z = static_cast<float>(posDist(engine));

		//	色の乱数の取得
		float r = static_cast<float>(colorDist(engine));
		float g = static_cast<float>(colorDist(engine));
		float b = static_cast<float>(colorDist(engine));

		//	速度の乱数の取得
		m_particleVel_Y[i] = static_cast<float>(velDist(engine));

		//	座標の設定
		m_particlePos[i] = SimpleMath::Vector3(pos_x, MAX_POSITION, pos_z);
		//	色の設定
		m_particleColor[i] = SimpleMath::Vector4(r, g, b, 1.0f);
	}

	//	クラッカー音の再生
	GetAudioResources()->PlayCracker01SE();
	GetAudioResources()->PlayCracker02SE();
}

/// <summary>
/// パーティクルの停止
/// </summary>
void ConfettiParticle::Stop()
{
	//	非アクティブ状態にする
	SetActive(false);
}