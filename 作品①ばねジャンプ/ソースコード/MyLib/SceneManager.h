//--------------------------------------------------------------------------------------
// File: SceneManager.h
//
// シーン管理クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SCENE_MANAGER_DEFINED
#define SCENE_MANAGER_DEFINED

#include "MyLib/JsonManager.h"

class IScene;
class SystemWindow;
class FadeCloud;

/// <summary>
///	シーン管理クラス
/// </summary>
class SceneManager
{
public:
	//	シーン遷移
	enum class SceneState
	{
		FadeIn,		//	フェイドイン
		Main,		//	メイン
		FadeOut		//	フェイドアウト
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime);
	/// <summary>
	///	描画
	/// </summary>
	void Render();
	/// <summary>
	///	影描画
	/// </summary>
	void ShadowRender();

	/// <summary>
	/// シーンを設定（初期）
	/// </summary>
	/// <param name="scene">シーン基底クラスのポインタ</param>
	void SetScene(IScene* scene);
	/// <summary>
	/// 次のシーンを設定（シーン移動）
	/// </summary>
	/// <param name="scene">シーン基底クラスのポインタ</param>
	void SetNextScene(IScene* scene);

	/// <summary>
	/// シーン状態を取得
	/// </summary>
	/// <returns>シーン状態</returns>
	const SceneState& GetSceneState() { return m_sceneState; }

	/// <summary>
	/// システム設定の保存
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	void SaveSystem(const int& mouseNumber);

private:
	//	データアクセス用の文字列
	static const std::string DATA_STR;

private:
	//	現在のシーンポインタ
	IScene* m_nowScene;
	//	次のシーンポインタ
	IScene* m_nextScene;

	//	シーン状態
	SceneState m_sceneState;

	//	フェイド画像
	std::unique_ptr<FadeCloud> m_fade;
	//	設定画面
	std::unique_ptr<SystemWindow> m_system;

	//	jsonファイル
	nlohmann::json m_systemData;

private:
	/// <summary>
	/// シーンの削除
	/// </summary>
	void DeleteScene();
	/// <summary>
	/// インゲームの処理
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void MainUpdate(const float& elapsedTime);
};
#endif // !SCENE_MANAGER_DEFINED