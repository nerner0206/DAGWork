//--------------------------------------------------------------------------------------
// File: JumpParticle.cpp
//
// ジャンプパーティクルクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "JumpParticle.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  頂点の初期位置とテクスチャUVの定数
const VertexPositionTexture JumpParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.25f, 0.25f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.25f, 0.25f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.25f, -0.25f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.25f, -0.25f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cam">カメラクラスのポインタ</param>
JumpParticle::JumpParticle() :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One),
	m_timer(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
JumpParticle::~JumpParticle()
{

}

/// <summary>
/// 初期化
/// </summary>
void JumpParticle::Initialize()
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
	CreateWICTextureFromFile(
		device,
		DataPath::CLOUD_PARTICLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);

	//	パーティクルの数分だけ初期化
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	座標の追加
		m_particlePos.push_back(SimpleMath::Vector3::Zero);
		//	ベクトルの追加
		m_particleVel.push_back(SimpleMath::Vector3::Zero);
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void JumpParticle::Update(const float& elapsedTime)
{
	//	タイマーを増加
	m_timer += elapsedTime;

	//	拡大率の計算
	SimpleMath::Vector3 sca = SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3::One * 2.0f,
		SimpleMath::Vector3::Zero,
		m_timer);
	//	拡大率の設定
	SetSca(sca);

	//	1秒後停止
	if (m_timer >= 1.0f)
	{
		//	止める
		Stop();
		return;
	}

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		m_particleVel[i].x *= 0.99f;
		m_particleVel[i].z *= 0.99f;

		//	座標更新
		m_particlePos[i] += m_particleVel[i];
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void JumpParticle::Render(
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

	
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	SimpleMath::Matrix world = sca * trans;

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
		VertexPositionTexture vertex[4];

		//	座標
		for (int j = 0; j < 4; j++)
		{
			//	一枚目に定数を入れる
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
/// 終了
/// </summary>
void JumpParticle::Finalize()
{

}

/// <summary>
/// パーティクルの実行
/// </summary>
/// <param name="pos">座標</param>
void JumpParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	アクティブ状態にする
	SetActive(true);
	//	座標の設定
	SetPos(pos);

	//	タイマーを0にする
	m_timer = 0.0f;

	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	座標を設定
		m_particlePos[i] = SimpleMath::Vector3::Zero;

		//	角度
		float radian = XM_2PI / static_cast<float>(PARTICLE_NUMBER);

		//	ベクトル
		m_particleVel[i].x = 2.0f * cosf(radian * i);
		m_particleVel[i].y = 1.0f;
		m_particleVel[i].z = 2.0f * sinf(radian * i);

		//	ベクトルの正規化
		m_particleVel[i].Normalize();
		m_particleVel[i] *= 0.05f;
	}
}

/// <summary>
/// パーティクルの停止
/// </summary>
void JumpParticle::Stop()
{
	//	非アクティブ状態にする
	SetActive(false);
}