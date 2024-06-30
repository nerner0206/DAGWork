//--------------------------------------------------------------------------------------
// File: PlayCamera.cpp
//
// プレイカメラクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayCamera.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/Player/PlayerSpring.h"

#include "imgui.h"

using namespace DirectX;

//	データアクセス文字列配列
const std::string PlayCamera::DATA_STRING[DATA_NUMBER] = {
	"OffSet",
	"MaxOffSet_X",
	"MaxOffSet_Z",
	"MinOffSet_Z",
	"TargetDistance"};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="startPos">開始座標</param>
/// <param name="endPos">終了座標</param>
PlayCamera::PlayCamera(
	const DirectX::SimpleMath::Vector3& startPos,
	const DirectX::SimpleMath::Vector3& endPos) :
	m_swich(false),
	m_t(1.0f),
	m_timer(0.0f)
{
	//	データの読み込み
	m_cameraData = JsonManager::LoadFile(DataPath::PLAY_CAMERA_DATA_PATH);

	//	データを変数へ格納
	m_offset = SimpleMath::Vector3(
		m_cameraData[DATA_STRING[0]][0],
		m_cameraData[DATA_STRING[0]][1],
		m_cameraData[DATA_STRING[0]][2]);
	m_maxOffset_x = m_cameraData[DATA_STRING[1]];
	m_maxOffset_z = m_cameraData[DATA_STRING[2]];
	m_minOffset_z = m_cameraData[DATA_STRING[3]];
	m_targetDistance = m_cameraData[DATA_STRING[4]];

	//	座標の設定
	BeforeUpdate(0.0f, startPos, endPos, 1.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayCamera::~PlayCamera()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="player">プレイヤークラスのポインタ</param>
void PlayCamera::Update(const float& elapsedTime, Player* player)
{
	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	Ｃキーが押されたらカメラの位置を変更
	if (kbTracker->pressed.C) m_swich = !m_swich;

	//	オフセットの変更
	ChangeOffset(elapsedTime);

	//	プレイヤーばねクラスにキャスト
	PlayerSpring* spring = dynamic_cast<PlayerSpring*>(player->GetPlayerSpring());

	//	プレイヤーの座標
	SimpleMath::Vector3 pPos = spring->GetPos();
	//	プレイヤーのY座標拡大率
	float pSca_y = spring->GetSca().y;
	//	プレイヤーの前方方向
	SimpleMath::Vector3 pForward = spring->GetCollisionObject()->GetForward();

	//	座標の更新
	SimpleMath::Vector3 pos = EyeUpdate(pPos, pSca_y);
	//	目標座標の更新
	SimpleMath::Vector3 target = TargetUpdate(pPos, pForward, pSca_y);

	//	座標の設定
	SetPos(pos);
	//	目標座標の設定
	SetTargetPosition(target);

	//	ビュー行列の計算
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(GetPos(), GetTargetPosition(), SimpleMath::Vector3::Up);
	//	ビュー行列の設定
	SetViewMatrix(view);
}

/// <summary>
/// 開始前更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
/// <param name="startPos">開始座標</param>
/// <param name="endPos">終了座標</param>
/// <param name="duration">間隔</param>
/// <returns>更新終了フラグ</returns>
bool PlayCamera::BeforeUpdate(
	const float& elapsedTime,
	const DirectX::SimpleMath::Vector3& startPos,
	const DirectX::SimpleMath::Vector3& endPos,
	const float& duration)
{
	//	間隔が0秒以下
	if (duration <= 0.0f) return true;

	//	時間の増加
	m_timer += elapsedTime;

	//	時間の割合
	float t = m_timer / duration;

	//	座標の計算
	SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(endPos, startPos, t);
	//	オフセット
	SimpleMath::Vector3 offset = m_offset + SimpleMath::Vector3(0.0f, 0.0f, m_maxOffset_z);

	//	座標の設定
	SetPos(pos + offset);
	//	目標座標の設定
	SetTargetPosition(pos);

	//	ビュー行列の計算
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(GetPos(), GetTargetPosition(), SimpleMath::Vector3::Up);
	//	ビュー行列の設定
	SetViewMatrix(view);

	if (m_timer > duration) return true;
	return false;
}

/// <summary>
/// デバッグ用描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayCamera::DebugRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	UIの描画
	ImGui::SetNextWindowPos(ImVec2(300, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_::ImGuiCond_Always);

	ImGui::Begin("PlayCamera");
	float offset[3] = { m_offset.x, m_offset.y, m_offset.z };
	ImGui::InputFloat3(DATA_STRING[0].c_str(), offset);
	m_offset = SimpleMath::Vector3(offset[0], offset[1], offset[2]);

	ImGui::InputFloat(DATA_STRING[1].c_str(), &m_maxOffset_x);
	ImGui::InputFloat(DATA_STRING[2].c_str(), &m_maxOffset_z);
	ImGui::InputFloat(DATA_STRING[3].c_str(), &m_minOffset_z);
	ImGui::InputFloat(DATA_STRING[4].c_str(), &m_targetDistance);

	ImGui::End();
}

/// <summary>
/// オフセットの変更
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void PlayCamera::ChangeOffset(const float& elapsedTime)
{
	if (m_swich && m_t > 0.0f)
	{
		m_t -= elapsedTime;
		if (m_t < 0.0f) m_t = 0.0f;
	}
	else if (!m_swich && m_t < 1.0f)
	{
		m_t += elapsedTime;
		if (m_t > 1.0f) m_t = 1.0f;
	}

	//	x軸のずれの計算
	m_offset.x = GetUserResources()->Lerp(-m_maxOffset_x, m_maxOffset_x, m_t);
}

/// <summary>
/// 座標の更新
/// </summary>
/// <param name="pos">基準座標</param>
/// <param name="t">時間</param>
/// <returns>座標</returns>
DirectX::SimpleMath::Vector3 PlayCamera::EyeUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const float& t)
{
	//	座標の計算
	return SimpleMath::Vector3::Lerp(
		SimpleMath::Vector3(pos.x, pos.y + m_offset.y, pos.z - m_minOffset_z),
		SimpleMath::Vector3(pos.x, pos.y, pos.z + m_maxOffset_z) + m_offset,
		t);
}

/// <summary>
/// 目標座標の更新
/// </summary>
/// <param name="pos">基準座標</param>
/// <param name="forward">正面座標</param>
/// <param name="t">時間</param>
/// <returns>目標座標</returns>
DirectX::SimpleMath::Vector3 PlayCamera::TargetUpdate(
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& forward,
	const float& t)
{
	//	座標の計算
	return SimpleMath::Vector3::Lerp(
		pos + (forward * m_targetDistance),
		pos,
		t);
}

/// <summary>
/// データの保存
/// </summary>
void PlayCamera::SaveData()
{
	//	データの更新
	m_cameraData[DATA_STRING[0]][0] = m_offset.x;
	m_cameraData[DATA_STRING[0]][1] = m_offset.y;
	m_cameraData[DATA_STRING[0]][2] = m_offset.z;
	m_cameraData[DATA_STRING[1]] = m_maxOffset_x;
	m_cameraData[DATA_STRING[2]] = m_maxOffset_z;
	m_cameraData[DATA_STRING[3]] = m_minOffset_z;
	m_cameraData[DATA_STRING[4]] = m_targetDistance;

	//	データの保存
	JsonManager::SaveFile(DataPath::PLAY_CAMERA_DATA_PATH, m_cameraData);
}