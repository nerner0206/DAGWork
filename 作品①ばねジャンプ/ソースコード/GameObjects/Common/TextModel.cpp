//--------------------------------------------------------------------------------------
// File: TextModel.cpp
//
// 文字モデルクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TextModel.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
TextModel::TextModel() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{

}

/// <summary>
/// デストラクタ
/// </summary>
TextModel::~TextModel()
{
	
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="filePath">モデルのファイルパス</param>
void TextModel::Initialize(const wchar_t* filePath)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::TEXT_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	m_model = Model::CreateFromCMO(device, filePath, *fx);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void TextModel::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	//	モデルを描画
	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			GetUserResources()->GetShadowMap()->DrawShadow(context, true);
		}
	);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void TextModel::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	//	サイズ変更
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転を加える
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	座標を移動させる
	SimpleMath::Matrix pos = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	ワールド行列の計算
	m_world = sca * rot * pos;

	//	モデルを描画
	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			//	シャドウマップへ描画
			GetUserResources()->GetShadowMap()->DrawShadowMap(context);
		});
}

/// <summary>
/// 終了
/// </summary>
void TextModel::Finalize()
{
	//	モデルのリセット
	m_model.reset();
}