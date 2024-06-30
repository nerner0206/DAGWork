//--------------------------------------------------------------------------------------
// File: PlayerHead.cpp
//
// プレイヤー頭クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayerHead.h"

#include "GameObjects/PlayScene/Player/PlayerSpring.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"

#include "GameObjects/PlayScene/Particle/Particle.h"

using namespace DirectX;

//	頭のデフォルトサイズ
const SimpleMath::Vector3 PlayerHead::PLAYER_HEAD_SIZE = SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤークラスのポインタ</param>
/// <param name="parent">親のポインタ</param>
PlayerHead::PlayerHead(Player* p, PlayerComponent* parent) :
	PlayerComponent(p),
	m_hit(false)
{
	//	親ポインタの設定
	SetParent(parent);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHead::~PlayerHead()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
void PlayerHead::Initialize(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	m_model = Model::CreateFromCMO(device, DataPath::PLAYER_HEAD_MODEL_PATH, *fx);

	//	球の当たり判定の作成
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(position, 0.45f);
	//	当たり判定の設定
	SetCollisionObject(std::move(sphereCollider));

	//	リセットする
	Reset(position, rotate);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
/// <param name="stageObjects">ステージ管理クラスのポインタ</param>
void PlayerHead::Update(const float& elapsedTime, const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate, StageManager* stageManager)
{
	//	座標の更新
	SetPos(position);
	//	回転の更新
	SetRotQua(rotate);

	//	当たり判定の更新
	GetCollisionObject()->ColliderUpdate(GetPos());

	//	nullptrの場合、処理しない
	if (stageManager == nullptr) return;

	//	ステージオブジェクトを数だけ回す
	for (auto stageObj : stageManager->GetStageObjs())
	{
		//	当たり判定用クラス
		Collider collider;

		//	衝突判定
		if (collider.SphereToSphereCheck(GetCollisionObject(), stageObj->GetCollisionObject()) ||
			collider.SphereToBoxCheck(GetCollisionObject(), stageObj->GetCollisionObject()))
		{
			//	衝突
			m_hit = true;
			//	パーティクルの再生
			GetPlayer()->GetExplosionParticle()->Play(GetPos());

			//	プレイヤー移動量の削除
			PlayerSpring* spring = dynamic_cast<PlayerSpring*>(GetParent());
			spring->SetVelocity(SimpleMath::Vector3::Zero);
		}
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayerHead::Render(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	衝突時描画しない
	if (m_hit) return;

	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	モデルの描画
	m_model->Draw(context, *states, GetWorldMatrix(), view, proj, false, [&]()
		{
			shadowMap->DrawShadow(context, true);
		});
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayerHead::ShadowRender(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	衝突時描画しない
	if (m_hit) return;

	//	コンテキストの取得
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	//	共通ステートクラスの取得
	auto states = GetUserResources()->GetCommonStates();
	//	シャドウマップの取得
	auto shadowMap = GetUserResources()->GetShadowMap();

	//	サイズを掛ける
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(0.5f);
	//	回転を掛ける
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	移動させる
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());

	//	ワールド行列を計算する
	SimpleMath::Matrix world = sca * rot * trans;

	//	モデルの描画
	m_model->Draw(context, *states, world, view, proj, false, [&]() 
		{
			shadowMap->DrawShadowMap(context);
		});

	//	ワールド行列を設定する
	SetWorldMatrix(world);
}

/// <summary>
///	デバッグ描画
/// </summary>
void PlayerHead::DebugRender()
{
	
}

/// <summary>
/// 終了
/// </summary>
void PlayerHead::Finalize()
{
	m_model.reset();
}

//	リセット
void PlayerHead::Reset(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	位置を更新
	SetPos(position);
	//	回転を更新
	SetRotQua(rotate);

	//	当たり判定の座標を変換する
	GetCollisionObject()->ColliderUpdate(GetPos());

	//	判定の初期化
	m_hit = false;
}

/// <summary>
/// データの保存
/// </summary>
void PlayerHead::SaveData()
{

}