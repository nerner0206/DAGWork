//--------------------------------------------------------------------------------------
// File: Cloud.cpp
//
// 雲クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Cloud.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
Cloud::Cloud() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Cloud::~Cloud()
{
	
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="filePath">雲モデルのファイルパス</param>
void Cloud::Initialize(const wchar_t* filePath)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	m_model = Model::CreateFromCMO(device, filePath, *fx);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Cloud::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	モデルの描画
	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, false);
		});
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Cloud::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	サイズ変更
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転を加える
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	座標を移動させる
	SimpleMath::Matrix pos = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	行列を計算
	m_world = sca * rot * pos;

	//	モデルの描画
	m_model->Draw(context, *states, m_world, view, proj, false, [&]() 
		{
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// 終了
/// </summary>
void Cloud::Finalize()
{
	//	モデルのリセット
	m_model.reset();
}