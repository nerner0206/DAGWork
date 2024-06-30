//--------------------------------------------------------------------------------------
// File: Goal.cpp
//
// ゴールクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Goal.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
Goal::Goal(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca) :
	Ground(pos, rot, sca)
{
	SetStageObjType(StageObjType::Goal);
}

/// <summary>
/// デストラクタ
/// </summary>
Goal::~Goal()
{

}

/// <summary>
/// 初期化
/// </summary>
void Goal::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_GOAL_MODEL_PATH, *fx);
	//	モデルを設定する
	SetModel(std::move(model));

	//	当たり判定を生成
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の情報を更新する
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の設定
	SetCollisionObject(std::move(boxCollider));
}

/// <summary>
/// デバッグ描画
/// </summary>
void Goal::DebugRender()
{
	//	ステージオブジェクトの種類
	ImGui::Text("Goal");
	//	共通デバッグ描画
	CommonDebugRender();
}

/// <summary>
/// 終了
/// </summary>
void Goal::Finalize()
{
}
