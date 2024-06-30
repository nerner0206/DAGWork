//--------------------------------------------------------------------------------------
// File: StageManager.h
//
// ステージ管理クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef STAGE_MANAGER_DEFINED
#define STAGE_MANAGER_DEFINED

#include "IStageObject.h"
#include "Start.h"
#include "MyLib/JsonManager.h"

class Player;

/// <summary>
/// ステージ管理クラス
/// </summary>
class StageManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	/// <param name="player">プレイヤークラスのポインタ</param>
	void Initialize(const int& stageNum, Player* player);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugRender();
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
	/// <summary>
	/// データの保存
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	void SaveData(const int& stageNum);

	/// <summary>
	/// ステージオブジェクトクラスのポインタ配列
	/// </summary>
	/// <returns>ステージオブジェクトクラスのポインタ配列</returns>
	std::vector<IStageObject*> GetStageObjs() { return m_stageObjs; }

	/// <summary>
	/// ゴールの取得
	/// </summary>
	/// <returns>ゴールクラスのポインタ</returns>
	IStageObject* GetGoal() { return m_goal.get(); }

	/// <summary>
	/// 初期座標の取得
	/// </summary>
	/// <returns>初期座標</returns>
	const DirectX::SimpleMath::Vector3& GetStartPosition() { return Start::START_POSITION; }

public:
	//	jsonファイルの最初の文字列
	const static std::string FIRST_STR;

	const static int OBJ_INFO_NUM = 4;
	//	jsonファイルの文字列
	const static std::string OBJ_INFO_STR[OBJ_INFO_NUM];

private:
	//	jsonファイル
	nlohmann::json m_stageData;

	//	スタートクラスのユニークポインタ
	std::unique_ptr<Start> m_start;
	//	ゴールクラスのユニークポインタ
	std::unique_ptr<IStageObject> m_goal;
	//	ステージオブジェクトクラスのポインタ配列
	std::vector<IStageObject*> m_stageObjs;
	//	風クラスのユニークポインタ配列
	std::vector<std::unique_ptr<IStageObject>> m_winds;

	//	ステージオブジェクトクラスのポインタ配列
	std::vector<IStageObject*> m_debugObjs;

	//	デバッグ番号
	int m_debugNumber;

private:

	/// <summary>
	/// ステージオブジェクトの生成
	/// </summary>
	/// <param name="objNum">オブジェクト番号</param>
	/// <param name="type">ステージ種類</param>
	/// <param name="player">プレイヤークラスのポインタ</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	void CreateObj(
		const int& objNum,
		const StageObjType& type,
		Player* player,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca);
};
#endif // !STAGE_MANAGER_DEFINED
