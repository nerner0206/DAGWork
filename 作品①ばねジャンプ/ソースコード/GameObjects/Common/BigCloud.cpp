//--------------------------------------------------------------------------------------
// File: BigCloud.h
//
// 大きい雲クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BigCloud.h"

#include "MyLib/IScene.h"
#include "MyLib/BinaryFile.h"

#include <iomanip>

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーンクラスのポインタ</param>
BigCloud::BigCloud(IScene* scene) :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One),
	m_nowScene(scene)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BigCloud::~BigCloud()
{

}

/// <summary>
/// 初期化
/// </summary>
void BigCloud::Initialize(const DirectX::SimpleMath::Vector3& pos, const float& sca)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();
	
	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	m_model = Model::CreateFromCMO(device, DataPath::BIG_CLOUD_MODEL_PATH, *fx);

	//	シェーダー作成
	CreateShader();

	//	座標の設定
	SetPos(pos);
	//	拡大率の設定
	SetSca(SimpleMath::Vector3::One * sca);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void BigCloud::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートの取得
	auto states = GetUserResources()->GetCommonStates();
	//	ステップタイマーの取得
	auto stepTimer = GetUserResources()->GetStepTimer();
	
	//	ライトの座標
	SimpleMath::Vector3 lightPosition = m_nowScene->GetLightPos();
	//	ライトの目標座標
	SimpleMath::Vector3 lightTarget = m_nowScene->GetLightTarget();
	//	ライトの方向ベクトル
	SimpleMath::Vector3 lightDir = lightTarget - lightPosition;

	//	ワールド座標の計算
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	サイズを掛ける
	world *= SimpleMath::Matrix::CreateScale(GetSca());
	//	回転を掛ける
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	座標を掛ける
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	モデルの描画
	m_model->Draw(context, *states, world, view, proj, false, [&]()
		{
			// 定数バッファを更新
			D3D11_MAPPED_SUBRESOURCE mappedResource;

			// GPUが定数バッファに対してアクセスを行わないようにする
			context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

			// 定数バッファを更新
			ConstantBuffer cb = {};
			cb.LightViewProj = SimpleMath::Matrix::Identity;
			cb.LightPos = SimpleMath::Vector4(lightPosition.x, lightPosition.y, lightPosition.z, 0.0f);
			cb.LightDir = SimpleMath::Vector4(lightDir.x, lightDir.y, lightDir.z, stepTimer->GetTotalSeconds() / 10.0f);

			*static_cast<ConstantBuffer*>(mappedResource.pData) = cb;

			// GPUが定数バッファに対してのアクセスを許可する
			context->Unmap(m_constantBuffer.Get(), 0);

			// ピクセルシェーダ使用する定数バッファを設定
			ID3D11Buffer* cbuf_ps[] = { m_constantBuffer.Get() };
			context->VSSetConstantBuffers(1, 1, cbuf_ps);
			context->PSSetConstantBuffers(1, 1, cbuf_ps);	// スロット０はDirectXTKが使用しているのでスロット１を使用する

			//	両面描画(処理が重たくなってしまう)
			context->RSSetState(states->CullNone());

			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
		});
}

/// <summary>
/// 終了
/// </summary>
void BigCloud::Finalize()
{
	//	ポインタにnullptr
	m_nowScene = nullptr;

	//	モデルのリセット
	m_model.reset();
}

/// <summary>
/// シェーダの作成
/// </summary>
void BigCloud::CreateShader()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	//	データの読み込み
	BinaryFile VSData = BinaryFile::LoadFile(DataPath::BIG_CLOUD_VS_PATH);
	BinaryFile PSData = BinaryFile::LoadFile(DataPath::BIG_CLOUD_PS_PATH);

	//	頂点シェーダ作成
	if (FAILED(
		device->CreateVertexShader(VSData.GetData(),VSData.GetSize(),NULL,m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	//	ピクセルシェーダ作成
	if (FAILED(
		device->CreatePixelShader(PSData.GetData(),PSData.GetSize(),NULL,m_pixelShader.ReleaseAndGetAddressOf())))
	{
		//	エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// 定数バッファの作成
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer));	// 確保するサイズ（16の倍数で設定する）
	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));
}