//--------------------------------------------------------------------------------------
// File: Start.cpp
//
// スタートクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Start.h"

#include "MyLib/UserResources.h"
#include "Game/DataPath.h"

using namespace DirectX;

//	開始座標
const SimpleMath::Vector3 Start::START_POSITION = SimpleMath::Vector3(0.0f, 2.0f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
Start::Start() :
	Object(START_POSITION, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Start::~Start()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">座標</param>
void Start::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの生成
	m_model = Model::CreateFromCMO(device, DataPath::STAGE_START_MODEL_PATH, *fx);

	//	ワールド行列の計算
	m_world = SimpleMath::Matrix::CreateTranslation(GetPos());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Start::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();

	//	モデルの描画
	m_model->Draw(context, *states, m_world, view, proj);
}

/// <summary>
/// デバッグ描画
/// </summary>
void Start::DebugRender()
{

}

/// <summary>
/// 終了
/// </summary>
void Start::Finalize()
{
	//	モデルのリセット
	m_model.reset();
}
