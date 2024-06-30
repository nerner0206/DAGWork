//--------------------------------------------------------------------------------------
// File: StageManager.cpp
//
// ステージ管理クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "StageManager.h"

#include "GameObjects/PlayScene/StageObjects/Factory/StageFactory.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/Start.h"

#include <sstream>

//	jsonファイルの最初の文字列
const std::string StageManager::FIRST_STR = "StageObj_list";
//	jsonファイルの文字列
const std::string StageManager::OBJ_INFO_STR[OBJ_INFO_NUM] = { "Type", "Position", "Rotation", "Scale" };

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
StageManager::StageManager() :
	m_debugNumber(0)
{

}

/// <summary>
/// デストラクタ
/// </summary>
StageManager::~StageManager()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="stageNum">ステージ番号</param>
/// <param name="player">プレイヤークラスのポインタ</param>
void StageManager::Initialize(const int& stageNum, Player* player)
{
	//	ステージjsonの読み込み
	m_stageData = JsonManager::LoadFile(DataPath::STAGE_DATA_PATHs[stageNum]);

	//	スタートの生成
	m_start = std::make_unique<Start>();
	m_start->Initialize();

	//	ステージオブジェクトの数
	int objNum = m_stageData[FIRST_STR].size();
	//	ステージオブジェクトの数だけ生成する
	for (int i = 0; i < objNum; i++)
	{
		//	オブジェクトの種類
		int type_num = m_stageData[FIRST_STR][i][OBJ_INFO_STR[0]];

		//	オブジェクトの座標
		SimpleMath::Vector3 pos = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][2]);
		//	オブジェクトの回転
		SimpleMath::Vector3 rot = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][2]);
		//	オブジェクトのサイズ
		SimpleMath::Vector3 size = SimpleMath::Vector3(
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][0],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][1],
			m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][2]);
		
		//	ステージオブジェクトの生成
		CreateObj(i, static_cast<StageObjType>(type_num), player, pos, rot, size);
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void StageManager::Update(const float& elapsedTime)
{
	for (auto& obj : m_stageObjs)
	{
		//	ステージブロックの更新
		obj->Update(elapsedTime);
	}

	//	風の更新
	for (auto& wind : m_winds)
	{
		wind->Update(elapsedTime);
	}

	//	ゴールの更新
	m_goal->Update(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void StageManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& obj : m_stageObjs)
	{
		//	ステージブロックの更新
		obj->Render(view, proj);
	}

	//	風の更新
	for (auto& wind : m_winds)
	{
		wind->Render(view, proj);
	}

	//	ゴールの描画
	m_goal->Render(view, proj);
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void StageManager::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& obj : m_stageObjs)
	{
		//	ステージブロックの更新
		obj->ShadowRender(view, proj);
	}

	m_goal->ShadowRender(view, proj);
}

/// <summary>
/// デバッグ描画
/// </summary>
void StageManager::DebugRender()
{
	//	ウィンドウの設定
	ImGui::SetNextWindowPos(ImVec2(980, 0), ImGuiCond_::ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 350), ImGuiCond_::ImGuiCond_Always);

	ImGui::Begin("StageObject");

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) 
	{ 
		m_debugNumber--;
		if (m_debugNumber < 0) m_debugNumber = m_debugObjs.size() - 1;
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
		m_debugNumber++;
		if (m_debugNumber >= m_debugObjs.size()) m_debugNumber = 0;
	}
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_debugNumber + 1);

	m_debugObjs[m_debugNumber]->DebugRender();

	ImGui::End();
}

/// <summary>
/// 終了
/// </summary>
void StageManager::Finalize()
{
	//	全てのポインタを消す
	for (auto& debugObj : m_debugObjs)
	{
		debugObj = nullptr;
	}
	//	配列を削除する
	m_debugObjs.clear();

	for (int i = 0; i < m_stageObjs.size(); i++)
	{
		//	ステージブロックの終了処理
		m_stageObjs[i]->Finalize();
		//	削除する
		delete m_stageObjs[i];
	}

	//	風の更新
	for (auto& wind : m_winds)
	{
		wind->Finalize();
	}
	
	//	クリア
	m_stageObjs.clear();

	m_goal->Finalize();
}

/// <summary>
/// リセット
/// </summary>
void StageManager::Reset()
{
	//	ステージオブジェクトのリセット
	for (auto& obj : m_stageObjs)
	{
		obj->Reset();
	}
}

/// <summary>
/// データの保存
/// </summary>
/// <param name="stageNum">ステージ番号</param>
void StageManager::SaveData(const int& stageNum)
{
	//	基本情報の保存
	for (int i = 0; i < m_debugObjs.size(); i++)
	{
		//	座標の変更
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][0] = m_debugObjs[i]->GetPos().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][1] = m_debugObjs[i]->GetPos().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[1]][2] = m_debugObjs[i]->GetPos().z;
		//	回転の変更
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][0] = m_debugObjs[i]->GetRot().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][1] = m_debugObjs[i]->GetRot().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[2]][2] = m_debugObjs[i]->GetRot().z;
		//	拡大率の変更
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][0] = m_debugObjs[i]->GetSca().x;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][1] = m_debugObjs[i]->GetSca().y;
		m_stageData[FIRST_STR][i][OBJ_INFO_STR[3]][2] = m_debugObjs[i]->GetSca().z;

		//	風
		if (m_debugObjs[i]->GetStageObjType() == StageObjType::Wind)
			m_stageData[FIRST_STR][i][Wind::POWER_STR] = dynamic_cast<Wind*>(m_debugObjs[i])->GetPower();
		//	動く雲
		else if (m_debugObjs[i]->GetStageObjType() == StageObjType::MoveCloud)
		{
			//	速度
			m_stageData[FIRST_STR][i][MoveGround::SPEED_STR] = dynamic_cast<MoveGround*>(m_debugObjs[i])->GetSpeed();
		}
	}

	//	保存
	JsonManager::SaveFile(DataPath::STAGE_DATA_PATHs[stageNum], m_stageData);
}

/// <summary>
/// ステージオブジェクトの生成
/// </summary>
/// <param name="objNum">オブジェクト番号</param>
/// <param name="type">ステージ種類</param>
/// <param name="player">プレイヤークラスのポインタ</param>
/// <param name="pos">座標</param>
/// <param name="rot">回転ベクトル</param>
/// <param name="sca">拡大率</param>
void StageManager::CreateObj(
	const int& objNum,
	const StageObjType& type,
	Player* player,
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& rot,
	const DirectX::SimpleMath::Vector3& sca)
{
	//	ゴール
	if (type == StageObjType::Goal)
	{
		//	生成
		m_goal = StageFactory::CreateGoal(pos, rot, sca);
		//	デバッグ用配列へ格納
		m_debugObjs.push_back(m_goal.get());

		//	処理終了
		return;
	}

	//	風
	if (type == StageObjType::Wind)
	{
		//	生成
		std::unique_ptr<Wind> wind = StageFactory::CreateWind(pos, rot, sca,
			m_stageData[FIRST_STR][objNum][Wind::POWER_STR]);
		//	プレイヤーの設定
		wind->SetPlayer(player);
		//	配列へ格納
		m_winds.push_back(std::move(wind));
		//	デバッグ用配列へ格納
		m_debugObjs.push_back(m_winds[m_winds.size() - 1].get());

		//	処理終了
		return;
	}

	//	格納用クラス
	IStageObject* stageObj = nullptr;

	//	普通雲
	if (type == StageObjType::Cloud)
		stageObj = StageFactory::CreateGround(pos, rot, sca);

	//	動く雲
	else if (type == StageObjType::MoveCloud)
	{
		//	移動先の配列
		std::vector<SimpleMath::Vector3> poses;
		//	最初の座標の追加
		poses.push_back(pos);

		//	移動座標の数
		int posNum = m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR].size();

		for (int i = 0; i < posNum; i++)
		{
			//	座標
			SimpleMath::Vector3 position = SimpleMath::Vector3(
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][0],
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][1],
				m_stageData[FIRST_STR][objNum][MoveGround::POSITIONS_STR][i][2]);

			//	座標の追加
			poses.push_back(position);
		}

		//	速度
		stageObj = StageFactory::CreateMoveGround(poses, rot, sca,
			m_stageData[FIRST_STR][objNum][MoveGround::SPEED_STR]);
	}

	//	風船
	else if(type == StageObjType::Balloon)
		stageObj = StageFactory::CreateBalloon(pos, rot, sca);
	
	//	nullptrなら処理しない
	if (stageObj == nullptr) return;

	//	配列に格納する
	m_stageObjs.push_back(stageObj);
	//	デバッグ用配列へ格納
	m_debugObjs.push_back(stageObj);
}