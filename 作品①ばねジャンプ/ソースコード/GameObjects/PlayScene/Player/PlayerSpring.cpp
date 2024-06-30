//--------------------------------------------------------------------------------------
// File: PlayerSpring.cpp
//
// プレイヤーばねクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayerSpring.h"

#include "SpringState/SpringStateDefault.h"
#include "SpringState/SpringStateShrink.h"

#include "SpringParts/SpringPart.h"

#include "GameObjects/PlayScene/Player/PlayerHead.h"
#include "GameObjects/PlayScene/CollisionObjects/SphereCollider.h"
#include "GameObjects/PlayScene/CollisionObjects/Collider.h"

#include "GameObjects/PlayScene/StageObjects/StageManager.h"
#include "GameObjects/PlayScene/StageObjects/Balloon.h"
#include "GameObjects/PlayScene/StageObjects/Ground.h"

#include "GameObjects/PlayScene/Player/SpringParts/PredictionLine.h"

#include "GameObjects/PlayScene/Particle/Particle.h"

using namespace DirectX;

//	データアクセス文字列配列
const std::string PlayerSpring::DATA_STRING[DATA_NUMBER] = {
	"JumpForce",
	"Gravity",
	"ShrinkSpeed",
	"ExtendSpeed",
	"XZForceRatio"};

//	当たり判定の半径
const float PlayerSpring::COLLISION_RADIUS = 0.3f;
//	球の当たり判定の位置
const SimpleMath::Vector3 PlayerSpring::COLLISION_POSITION_OFFSET = SimpleMath::Vector3(0.0f, -0.5f, 0.0f);
//	頭の位置
const SimpleMath::Vector3 PlayerSpring::HEAD_POSITION_OFFSET = SimpleMath::Vector3(0.0f, 0.8f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="p">プレイヤークラスのポインタ</param>
PlayerSpring::PlayerSpring(Player* p):
	PlayerComponent(p),
	m_nowSpringState(nullptr),
	m_nextSpringState(nullptr),
	m_isShrink(false),
	m_hitBalloon(nullptr),
	m_isGoal(false)
{
	//	データの読み込み
	m_springData = JsonManager::LoadFile(DataPath::PLAYER_SPRING_DATA_PATH);

	//	データを変数へ格納
	m_jumpForce = m_springData[DATA_STRING[0]];
	m_gravity = m_springData[DATA_STRING[1]];
	m_shrinkRatio = m_springData[DATA_STRING[2]];
	m_extendSpeed = m_springData[DATA_STRING[3]];
	m_XZForceRatio = m_springData[DATA_STRING[4]];
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerSpring::~PlayerSpring()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
void PlayerSpring::Initialize(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	パーツの生成
	for (int i = 0; i < DataPath::PLAYER_SPRING_MODEL_NUMBER; i++)
	{
		//	生成する
		std::unique_ptr<SpringPart> part = std::make_unique<SpringPart>();
		part->Initialize(DataPath::PLAYER_SPRING_MODEL_PATHs[i]);
		//	配列へ格納
		m_springParts.push_back(std::move(part));
	}

	//	当たり判定の生成
	std::unique_ptr<SphereCollider> sphereCollider = std::make_unique<SphereCollider>(
		position + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, rotate),
		COLLISION_RADIUS);
	//	当たり判定の設定
	SetCollisionObject(std::move(sphereCollider));

	//	プレイヤーの頭生成
	m_head = std::make_unique <PlayerHead>(GetPlayer(), this);
	m_head->Initialize(
		position + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET, rotate),
		rotate);
	//	子供の設定
	SetChild(m_head.get());

	//	予測線の生成
	m_line = std::make_unique<PredictionLine>();
	m_line->Initialize();

	//	リセット
	Reset(position, rotate);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転</param>
/// <param name="stageObjects">ステージ管理クラスのポインタ</param>
void PlayerSpring::Update(const float& elapsedTime, const SimpleMath::Vector3& position,
	const SimpleMath::Quaternion& rotate, StageManager* stageManager)
{
	//	予測線表示の切り替え
	ChangeDisplayLine();

	//	入力更新
	RotUpdate(elapsedTime);

	//	ばね状態の更新
	if (m_nowSpringState) m_nowSpringState->Update(elapsedTime);

	//	次の状態が存在する
	if (m_nextSpringState)
	{
		//	状態の設定
		SetState(m_nextSpringState);
		//	次の状態の削除
		m_nextSpringState = nullptr;
		return;
	}

	//	座標を取得
	SimpleMath::Vector3 pos = GetPos();

	//	当たり判定の座標を変換する
	GetCollisionObject()->ColliderUpdate(
		pos + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()));

	//	当たり判定クラス
	Collider collider;

	//	ステージオブジェクトとの当たり判定
	for (auto stageObj : stageManager->GetStageObjs())
	{
		//	非アクティブ状態なら処理しない
		if (!stageObj->GetIsHitActive()) continue;

		//	風船の場合
		if (stageObj->GetStageObjType() == StageObjType::Balloon)
		{
			//	衝突判定
			if (!collider.SphereToSphereCheck(GetCollisionObject(), stageObj->GetCollisionObject())) continue;
			//	めり込み補正
			pos += InImmersed(collider.GetDistance());

			//	触れた風船の格納
			m_hitBalloon = dynamic_cast<Balloon*>(stageObj);
		}
		else
		{
			//	衝突判定
			if (!collider.SphereToBoxCheck(GetCollisionObject(), stageObj->GetCollisionObject())) continue;
			//	めり込み補正
			pos += InImmersed(collider.GetDistance());

			//	雲を揺らす
			if (!m_isShrink) dynamic_cast<Ground*>(stageObj)->SetIsShake(true);
		}

		//	当たり判定の座標を変換する
		GetCollisionObject()->ColliderUpdate(
			pos + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()));

		//	衝突開始判定
		if (!m_isShrink)
		{
			//	ジャンプパーティクルの再生
			GetPlayer()->GetJumpParticle()->Play(GetCollisionObject()->GetPos());
			//	ばね音の再生
			GetAudioResources()->PlaySpringSE();
		}

		//	縮小中にする
		m_isShrink = true;
		//	縮み状態へ変更
		SetNextState(new SpringStateShrink(this));
	}

	//	更新処理
	m_head->Update(
		elapsedTime,
		pos + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua(),
		stageManager);

	//	ゴールの当たり判定
	m_isGoal = collider.SphereToBoxCheck(GetCollisionObject(), stageManager->GetGoal()->GetCollisionObject());

	//	座標の更新
	SetPos(pos);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayerSpring::Render(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	予測線の描画
	if(m_line->GetIsActive()) m_line->Render(view, proj);

	//	ばねのパーツの描画
	for (auto& part : m_springParts)
	{
		part->Render(GetWorldMatrix(), view, proj);
	}

	//	子供の描画
	m_head->Render(view, proj);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayerSpring::ShadowRender(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	サイズを掛ける
	SimpleMath::Matrix sca = SimpleMath::Matrix::CreateScale(GetSca());
	//	回転を掛ける
	SimpleMath::Matrix rot = SimpleMath::Matrix::CreateFromQuaternion(GetRotQua());
	//	移動させる
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPos());
	//	ワールド行列の設定
	SetWorldMatrix(sca * rot * trans);

	//	ばねのパーツの描画
	for (auto& part : m_springParts)
	{
		part->ShadowRender(GetWorldMatrix(), view, proj);
	}

	//	子供の描画
	m_head->ShadowRender(view, proj);
}

/// <summary>
/// デバッグ描画
/// </summary>
void PlayerSpring::DebugRender()
{
	ImGui::InputFloat(DATA_STRING[0].c_str(), &m_jumpForce);
	ImGui::InputFloat(DATA_STRING[1].c_str(), &m_gravity);
	ImGui::SliderFloat(DATA_STRING[2].c_str(), &m_shrinkRatio, 0.980f, 0.999f);
	ImGui::SliderFloat(DATA_STRING[3].c_str(), &m_extendSpeed, 0.01f, 0.1f);
	ImGui::SliderFloat(DATA_STRING[4].c_str(), &m_XZForceRatio, 1.0f, 2.0f);

	//	頭のデバッグ描画
	m_head->DebugRender();
}

/// <summary>
/// 終了
/// </summary>
void PlayerSpring::Finalize()
{
	//	状態の削除
	DeleteState();

	//	ばねのパーツの終了
	for (auto& part : m_springParts)
	{
		part->Finalize();
	}
	
	//	頭の終了
	m_head->Finalize();
}

//	リセット
void PlayerSpring::Reset(const SimpleMath::Vector3& position, const SimpleMath::Quaternion& rotate)
{
	//	座標
	SetPos(position);
	//	回転
	SetRotQua(rotate);
	//	拡大率
	SetSca(SimpleMath::Vector3::One);

	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();
	//	カーソル座標を戻す
	SetCursorPos(centerPos.x, centerPos.y);

	//	当たり判定の更新
	GetCollisionObject()->ColliderUpdate(
		GetPos() + SimpleMath::Vector3::Transform(COLLISION_POSITION_OFFSET, GetRotQua()),
		GetRotQua(),
		GetSca());

	// 頭のリセット
	m_head->Reset(
		GetPos() + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua());

	//	ベクトルのリセット
	m_velocity = SimpleMath::Vector3::Zero;
	//	縮み中
	m_isShrink = false;

	//	予測線のリセット
	m_line->Reset();

	//	通常状態の設定
	SetState(new SpringStateDefault(this));
}
/// <summary>
/// データの保存
/// </summary>
void PlayerSpring::SaveData()
{
	//	データを変数へ格納
	m_springData[DATA_STRING[0]] = m_jumpForce;
	m_springData[DATA_STRING[1]] = m_gravity;
	m_springData[DATA_STRING[2]] = m_shrinkRatio;
	m_springData[DATA_STRING[3]] = m_extendSpeed;
	m_springData[DATA_STRING[4]] = m_XZForceRatio;

	//	データの保存
	JsonManager::SaveFile(DataPath::PLAYER_SPRING_DATA_PATH, m_springData);

	//	頭データの保存
	m_head->SaveData();
}

/// <summary>
/// テスト更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void PlayerSpring::TestUpdate(const float& elapsedTime)
{
	//	入力更新
	RotUpdate(elapsedTime);

	//	更新処理
	m_head->Update(
		elapsedTime,
		GetPos() + SimpleMath::Vector3::Transform(HEAD_POSITION_OFFSET * GetSca().y, GetRotQua()),
		GetRotQua(),
		nullptr);
}

/// <summary>
/// 次の状態の設定
/// </summary>
/// <param name="state">ばね状態クラスのポインタ</param>
void PlayerSpring::SetNextState(SpringState* state)
{
	if (m_nextSpringState || !state) return;

	// シーンを生成
	m_nextSpringState = state;
}

/// <summary>
/// 状態の設定
/// </summary>
/// <param name="state">ばね状態クラスのポインタ</param>
void PlayerSpring::SetState(SpringState* state)
{
	//	ポインタが無い場合、処理しない
	if (!state) return;

	//	状態の削除
	DeleteState();

	//	状態の設定
	m_nowSpringState = state;
	//	初期化
	m_nowSpringState->Initialize();
}

/// <summary>
///	風船の破壊
/// </summary>
void PlayerSpring::BreakBalloon()
{
	//	風船が無い場合、処理しない
	if (!m_hitBalloon) return;

	//	風船を割る
	m_hitBalloon->Break();
	m_hitBalloon = nullptr;
}

/// <summary>
/// 状態の削除
/// </summary>
void PlayerSpring::DeleteState()
{
	//	ポインタが存在しない場合、処理しない
	if (!m_nowSpringState) return;
	
	//	終了
	m_nowSpringState->Finalize();

	//	状態の削除
	delete m_nowSpringState;
	//	nullptrの格納
	m_nowSpringState = nullptr;
}

/// <summary>
/// 回転更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void PlayerSpring::RotUpdate(const float& elapsedTime)
{
	//	マウスの現在の座標
	Mouse::State mo = Mouse::Get().GetState();
	SimpleMath::Vector2 nowMousePos = SimpleMath::Vector2(mo.x, mo.y);

	SimpleMath::Vector2 centerPos = GetUserResources()->GetCenterPos();

	//	マウスの移動量
	SimpleMath::Vector2 mouseVel = (nowMousePos - centerPos) * GetPlayer()->GetMouseSensitivity();

	//	カーソル座標を戻す
	SetCursorPos(centerPos.x, centerPos.y);

	//if (mx <= 0 && my <= 0) return;

	//	回転量
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;

	//	回転量の計算
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(-mouseVel.x));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(mouseVel.y));

	//	回転の乗算
	SimpleMath::Quaternion rotate = GetRotQua() * q;
	//	回転の保存
	SetRotQua(rotate);

	//	予測線計算(縮小中)
	if(m_isShrink) PreLine(elapsedTime);
}
/// <summary>
/// めり込み補正
/// </summary>
/// <param name="distance">めり込み量</param>
/// <returns>補正ベクトル</returns>
SimpleMath::Vector3 PlayerSpring::InImmersed(const float& distance)
{
	//	反転ベクトル
	SimpleMath::Vector3 vel = -m_velocity;
	//	ベクトルの正規化
	vel.Normalize();

	//	めり込み量の押し出し
	vel *= distance;
	//	速度の相殺
	m_velocity *= 0.0f;

	return vel;
}

/// <summary>
/// 予測線表示の切り替え
/// </summary>
void PlayerSpring::ChangeDisplayLine()
{
	//	キーボードステートトラッカー
	auto key = GetUserResources()->GetKeyboardStateTracker();

	//	Xキーが押された瞬間
	if (key->IsKeyPressed(Keyboard::Keys::X))
	{
		//	予測線表示の切り替え
		bool flag = m_line->GetIsActive();
		m_line->SetIsActive(!flag);
		//	リセット
		m_line->Reset();
	}
}

/// <summary>
///	予測線の計算
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void PlayerSpring::PreLine(const float& elapsedTime)
{
	//	計測用
	float timer = 0.0f;

	//	配列をクリアする
	m_line->Reset();

	//	座標の取得
	SimpleMath::Vector3 pos = GetPos();
	//	跳ね返り力
	SimpleMath::Vector3 vel = SimpleMath::Vector3::Transform(
		SimpleMath::Vector3(0.0f, m_jumpForce, 0.0f), GetRotQua());

	//	３秒間の座標を予測する
	while (timer < PredictionLine::PREDICTION_TIME)
	{
		//	時間の増加
		timer += elapsedTime;

		//	重力の加算
		vel.y -= m_gravity;
		//	速度の加算
		pos += (vel * elapsedTime);

		m_line->AddPosition(pos);
	}
}