//--------------------------------------------------------------------------------------
// File: MoveGround.cpp
//
// 動く足場クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "MoveGround.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

//	データアクセス用文字列
const std::string MoveGround::POSITIONS_STR = "PositionList";
//	データアクセス用文字列
const std::string MoveGround::SPEED_STR = "Speed";

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
/// <param name="speed">速度</param>
MoveGround::MoveGround(
	const std::vector<DirectX::SimpleMath::Vector3>& poses,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca,
	const float& speed) :
	Ground(poses[0], rot, sca),
	m_poses(poses),
	m_speed(speed),
	m_num(0),
	m_nextNum(1),
	m_time(1.0f),
	m_timer(0.0f)
{
	SetStageObjType(StageObjType::MoveCloud);
}

/// <summary>
/// デストラクタ
/// </summary>
MoveGround::~MoveGround()
{

}

/// <summary>
/// 初期化
/// </summary>
void MoveGround::Initialize()
{
	//	デバイスの取得
	auto device = GetUserResources()->GetDeviceResources()->GetD3DDevice();

	// エフェクトファクトリーの作成
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH);

	//	モデルの作成
	std::unique_ptr<Model> model = Model::CreateFromCMO(device, DataPath::STAGE_CLOUD_MODEL_PATH, *fx);
	//	モデルの設定
	SetModel(std::move(model));

	//	当たり判定を生成
	std::unique_ptr<BoxCollider> boxCollider = std::make_unique<BoxCollider>(GetPos(), GetRotQua(), GetSca());

	//	当たり判定の情報を更新する
	boxCollider->ColliderUpdate(GetPos(), GetRotQua(), GetSca());

	//	当たり判定を設定する
	SetCollisionObject(std::move(boxCollider));

	m_num = 0;
	m_nextNum = 1;

	//	目標への距離
	float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
	//	目標まで掛かる時間
	m_time = length / m_speed;

	//	タイマーの初期化
	m_timer = 0;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void MoveGround::Update(const float& elapsedTime)
{
	//	雲の揺れ
	Shaking(elapsedTime);

	//	時間の増加
	m_timer += elapsedTime;
	if (m_timer > m_time) m_timer = m_time;

	//	座標の計算
	SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(
		m_poses[m_num],
		m_poses[m_nextNum],
		m_timer / m_time);

	//	次の目標座標へ
	if (m_timer >= m_time)
	{
		//	次の座標番号へ
		m_num++;
		if (m_num >= m_poses.size()) m_num = 0;
		m_nextNum = m_num + 1;
		if (m_nextNum >= m_poses.size()) m_nextNum = 0;

		//	目標への距離
		float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
		//	目標まで掛かる時間
		m_time = length / m_speed;

		//	タイマーの初期化
		m_timer = 0;
	}

	//	座標の設定
	SetPos(pos);

	//	当たり判定の更新
	GetCollisionObject()->ColliderUpdate(GetPos(), GetRotQua(), GetSca());
}


/// <summary>
/// デバッグ描画
/// </summary>
void MoveGround::DebugRender()
{
	//	ステージオブジェクトの種類
	ImGui::Text("MoveCloud");
	//	共通デバッグ描画
	CommonDebugRender();
	//	速度の変更
	ImGui::InputFloat(SPEED_STR.c_str(), &m_speed);
}

/// <summary>
/// 終了
/// </summary>
void MoveGround::Finalize()
{

}

/// <summary>
/// リセット
/// </summary>
void MoveGround::Reset()
{
	//	座標の設定
	SetPos(m_poses[0]);

	m_num = 0;
	m_nextNum = 1;

	//	目標への距離
	float length = (m_poses[m_nextNum] - m_poses[m_num]).Length();
	//	目標まで掛かる時間
	m_time = length / m_speed;

	//	タイマーの初期化
	m_timer = 0;
}
