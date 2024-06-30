//--------------------------------------------------------------------------------------
// File: SpringPart.cpp
//
// プレイヤーばねの部品クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringPart.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SpringPart::SpringPart() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
SpringPart::~SpringPart()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="fileName">モデルのファイルパス</param>
void SpringPart::Initialize(const wchar_t* fileName)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの生成
	m_model = Model::CreateFromCMO(device, fileName, *fx);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
void SpringPart::Update(
	const float& elapsedTime,
	const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate)
{

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void SpringPart::Render(
	const SimpleMath::Matrix& world,
	const SimpleMath::Matrix& view,
	const SimpleMath::Matrix& proj)
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();
	auto shadowMap = GetUserResources()->GetShadowMap();

	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, true);
		}
	);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void SpringPart::ShadowRender(
	const SimpleMath::Matrix& world,
	const SimpleMath::Matrix& view,
	const SimpleMath::Matrix& proj)
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	移動させる
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());
	//	回転を掛ける
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());

	m_world = rot * world  * trans;

	m_model->Draw(context, *states, m_world, view, proj, false, [&]()
		{
			// シャドウマップへ描画
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// 終了
/// </summary>
void SpringPart::Finalize()
{
	m_model.reset();
}