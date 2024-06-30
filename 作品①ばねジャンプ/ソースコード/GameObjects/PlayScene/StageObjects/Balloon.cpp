//--------------------------------------------------------------------------------------
// File: Balloon.cpp
//
// 風船クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Balloon.h"

#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
Balloon::Balloon(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	IStageObject(StageObjType::Balloon, pos, rot, sca)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Balloon::~Balloon()
{
	
}

/// <summary>
/// 初期化
/// </summary>
void Balloon::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_BALLOON_MODEL_PATH, *fx);
	//	モデルの設定
	SetModel(std::move(model));

	//	当たり判定の生成
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(GetPos(), 1.0f);
	//	当たり判定の情報を更新する
	sphereCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の設定
	SetCollisionObject(std::move(sphereCollider));
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void Balloon::Update(const float& elapsedTime)
{
	
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Balloon::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!GetIsHitActive()) return;

	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();
	
	//	モデルの描画
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, false);
		});
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Balloon::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (!GetIsHitActive()) return;

	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	拡大率
	SimpleMath::Matrix p_sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転
	SimpleMath::Matrix p_rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	移動
	SimpleMath::Matrix p_trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	ワールド行列の計算
	SimpleMath::Matrix world = p_sca * p_rot * p_trans;
	SetWorldMatrix(world);

	//	モデルの描画
	GetModel()->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadowMap(context);
		});
}

/// <summary>
/// デバッグ描画
/// </summary>
void Balloon::DebugRender()
{
	//	ステージオブジェクトの種類
	ImGui::Text("Balloon");
	//	共通デバッグ描画
	CommonDebugRender();
}

/// <summary>
/// 終了
/// </summary>
void Balloon::Finalize()
{

}

/// <summary>
/// リセット
/// </summary>
void Balloon::Reset()
{
	//	アクティブ状態をtrueへ
	SetIsHitActive(true);
}

/// <summary>
/// 割れる
/// </summary>
void Balloon::Break()
{
	//	破裂音の再生
	GetAudioResources()->PlayBalloonSE();

	//	アクティブ状態をfalseへ
	SetIsHitActive(false);
}
