//--------------------------------------------------------------------------------------
// File: WindParticle.cpp
//
// 風パーティクルクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "WindParticle.h"

#include "GameObjects/PlayScene/StageObjects/Wind.h"

#include <WICTextureLoader.h> 

using namespace DirectX;

//  頂点の初期位置とテクスチャUVの定数
const VertexPositionTexture WindParticle::VERTICES[4] =
{
		VertexPositionTexture(SimpleMath::Vector3(-0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.1f, 0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 0.0f)),
		VertexPositionTexture(SimpleMath::Vector3(0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(1.0f, 1.0f)),
		VertexPositionTexture(SimpleMath::Vector3(-0.1f, -0.1f, 0.0f),	SimpleMath::Vector2(0.0f, 1.0f)),
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="wind">風クラスのポインタ</param>
WindParticle::WindParticle(Wind* wind) :
	Particle(
		SimpleMath::Vector3::Zero,
		SimpleMath::Quaternion::Identity,
		SimpleMath::Vector3::One),
	m_timer(0.0f),
	m_wind(wind)
{

}

/// <summary>
/// デストラクタ
/// </summary>
WindParticle::~WindParticle()
{

}

/// <summary>
/// 初期化
/// </summary>
void WindParticle::Initialize()
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
		DataPath::WIND_PARTICLE_IMAGE_PATH,
		nullptr,
		m_texture.GetAddressOf()
	);

	//	力の向きの取得
	SimpleMath::Vector3 forward = m_wind->GetVector();

	//	垂直方向
	SimpleMath::Vector3 vertical = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_wind->GetRotQua());
	//	水平方向
	SimpleMath::Vector3 horizontal = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX, m_wind->GetRotQua());

	SimpleMath::Vector3 offPos = (-vertical * m_wind->GetSca().y * 0.5f) + (-horizontal * m_wind->GetSca().x * 0.5f);

	//	パーティクルの数分だけ初期化
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		float x = i % 4;
		float y = i / 4;

		//	座標
		SimpleMath::Vector3 pos = offPos + (horizontal * m_wind->GetSca().x * 0.25f * x) + (vertical * m_wind->GetSca().y * 0.25f * y);
		SimpleMath::Vector3 startPos = pos + (-forward * m_wind->GetSca().z * 0.5f);

		//	開始座標の追加
		m_particleStartPos.push_back(startPos);

		//	座標の追加
		if(((i / 4) % 2 == 0 && i % 2 == 0) || ((i / 4) % 2 == 1 && i % 2 == 1)) m_particlePos.push_back(pos); 
		else m_particlePos.push_back(startPos);
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void WindParticle::Update(const float& elapsedTime)
{
	//	タイマーを増加
	m_timer += elapsedTime;

	//	力の向きの取得
	SimpleMath::Vector3 forward = m_wind->GetVector();

	//	垂直方向
	SimpleMath::Vector3 vertical = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitY, m_wind->GetRotQua());
	//	水平方向
	SimpleMath::Vector3 horizontal = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX, m_wind->GetRotQua());

	//	パーティクルの数分だけ初期化
	for (int i = 0; i < PARTICLE_NUMBER; i++)
	{
		//	移動させる
		m_particlePos[i] += (forward * m_wind->GetPower() * elapsedTime);
		//	開始位置との距離計算
		float l = (m_particleStartPos[i] - m_particlePos[i]).Length();
		//	拡大率より大きい場合戻す
		if (l > m_wind->GetSca().z) m_particlePos[i] = m_particleStartPos[i];
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
/// <param name="camera">カメラクラスのポインタ</param>
void WindParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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

	SimpleMath::Matrix world = SimpleMath::Matrix::CreateTranslation(m_wind->GetPos());

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

	//	徐々に透明にする
	m_batchEffect->SetAlpha(0.5f);

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
void WindParticle::Finalize()
{

}

/// <summary>
/// パーティクルの実行
/// </summary>
/// <param name="pos">座標</param>
void WindParticle::Play(const DirectX::SimpleMath::Vector3& pos)
{
	//	アクティブ状態にする
	SetActive(true);
	//	座標の設定
	SetPos(pos);

	//	タイマーを0にする
	m_timer = 0.0f;
}

/// <summary>
/// パーティクルの停止
/// </summary>
void WindParticle::Stop()
{
	//	非アクティブ状態にする
	SetActive(false);
}