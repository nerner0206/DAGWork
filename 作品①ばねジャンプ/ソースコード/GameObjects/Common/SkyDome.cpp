//--------------------------------------------------------------------------------------
// File: SkyDome.cpp
//
// スカイドームクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SkyDome.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SkyDome::SkyDome() :
	Object(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity, SimpleMath::Vector3::One)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	m_model = Model::CreateFromCMO(device, DataPath::SKYDOME_MODEL_PATH, *fx);
}

/// <summary>
/// デストラクタ
/// </summary>
SkyDome::~SkyDome()
{
	
}

/// <summary>
/// 自転
/// </summary>
/// <param name="speed">回転速度</param>
void SkyDome::RotUpdate(const float& speed)
{
	//	回転クォータニオン
	SimpleMath::Quaternion q, rotate = GetRotQua();

	//	回転させる
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(speed));
	rotate = q * rotate;

	//	設定
	SetRotQua(rotate);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートの取得
	auto states = GetUserResources()->GetCommonStates();
	
	//	ワールド座標の計算
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	//	サイズを掛ける
	world *= SimpleMath::Matrix::CreateScale(GetSca());
	//	回転を掛ける
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	座標を掛ける
	world *= SimpleMath::Matrix::CreateTranslation(GetPos());

	//	モデルのエフェクトを設定
	m_model->UpdateEffects([&](IEffect* effect)
		{
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				// ライトの影響をなくす
				lights->SetAmbientLightColor(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
		});

	//	モデルの描画
	m_model->Draw(context, *states, world, view, proj);
}

/// <summary>
/// 終了
/// </summary>
void SkyDome::Finalize()
{
	//	モデルのリセット
	m_model.reset();
}