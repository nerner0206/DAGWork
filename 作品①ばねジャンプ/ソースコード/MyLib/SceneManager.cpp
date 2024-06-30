//--------------------------------------------------------------------------------------
// File: SceneManager.cpp
//
// シーン管理クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SceneManager.h"

#include "GameObjects/Common/SystemWindow.h"
#include "GameObjects/Common/FadeCloud.h"

#include "MyLib/IScene.h"

using namespace DirectX;

//	データアクセス用の文字列
const std::string SceneManager::DATA_STR = "Sensitivity";

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager() :
	m_nowScene(nullptr),
	m_nextScene(nullptr),
	m_sceneState(SceneState::FadeIn)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	//	設定画面の終了
	m_system->Finalize();
	//	シーンの削除
	DeleteScene();
}

/// <summary>
/// 初期化
/// </summary>
void SceneManager::Initialize()
{
	//	ステージjsonの読み込み
	m_systemData = JsonManager::LoadFile(DataPath::SYSTEM_DATA_PATH);

	//	設定画面の生成
	m_system = std::make_unique<SystemWindow>();
	m_system->Initialize(m_systemData[DATA_STR]);

	//	フェイド用の雲の生成
	m_fade = std::make_unique<FadeCloud>();
	m_fade->Initialize();

	//	フェイドイン設定
	m_fade->FadeInStart();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void SceneManager::Update(const float& elapsedTime)
{
	//	設定画面の更新
	if (m_system->GetIsSystemOpen()) 
	{
		m_system->Update(m_nowScene);
		return;
	}

	//	フェイドイン処理
	if (m_sceneState == SceneState::FadeIn)
	{
		//	フェイドイン終了判定
		if (m_fade->FadeInUpdate(elapsedTime)) 
			m_sceneState = SceneState::Main;
	}
	//	フェイドアウト処理
	else if (m_sceneState == SceneState::FadeOut)
	{
		//	フェイドアウト終了判定
		if (m_fade->FadeOutUpdate(elapsedTime))
		{
			//	シーンの設定
			SetScene(m_nextScene);
			//	次のシーンを消す
			m_nextScene = nullptr;

			//	フェイドインへ
			m_sceneState = SceneState::FadeIn;
		}
		return;
	}

	//	ゲームの更新
	MainUpdate(elapsedTime);
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Render()
{
	//	シーンの描画
	if (m_nowScene) m_nowScene->Render();

	//	設定画面の描画
	if (m_system->GetIsSystemOpen()) m_system->Render();

	//	UIの描画
	if(m_sceneState != SceneState::Main) m_fade->Render();
}

/// <summary>
/// 影描画
/// </summary>
void SceneManager::ShadowRender()
{
	//	シーンの描画
	if (m_nowScene) m_nowScene->ShadowRender();
}

/// <summary>
/// シーンを設定（初期）
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
void SceneManager::SetScene(IScene* scene)
{
	// シーンを削除
	DeleteScene();

	// シーンを生成
	m_nowScene = scene;
	// シーンにシーンマネージャーへのポインタを設定
	m_nowScene->SetSceneManager(this);
	// シーンの初期化処理
	m_nowScene->Initialize(m_systemData[DATA_STR]);
}

/// <summary>
/// 次のシーンを設定（シーン移動）
/// </summary>
/// <param name="scene">シーン基底クラスのポインタ</param>
void SceneManager::SetNextScene(IScene* scene)
{
	if (m_nextScene) return;

	// シーンを生成
	m_nextScene = scene;
}

/// <summary>
/// シーンの削除
/// </summary>
void SceneManager::DeleteScene()
{
	//	現在のシーンが無ければ処理しない
	if (!m_nowScene) return;

	//	シーンの終了処理
	m_nowScene->Finalize();
	//	シーンの削除
	delete m_nowScene;
	//	nullptrを格納
	m_nowScene = nullptr;
}

/// <summary>
/// インゲームの処理
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void SceneManager::MainUpdate(const float& elapsedTime)
{
	//	シーンの切り替え
	if (m_nextScene && m_sceneState == SceneState::Main)
	{
		//	フェイドアウト
		m_sceneState = SceneState::FadeOut;
		m_fade->FadeOutStart();

		return;
	}

	//	キーボードステートトラッカー
	Keyboard::KeyboardStateTracker* kbTracker = UserResources::GetInstance()->GetKeyboardStateTracker();
	//	ESCキーが押されたら設定画面の開始
	if (kbTracker->pressed.Escape && m_sceneState == SceneState::Main)
	{
		//	設定画面を開く
		m_system->OnWindow(m_nowScene);
		return;
	}

	//	シーンの更新
	if (m_nowScene) m_nowScene->Update(elapsedTime);
}

/// <summary>
/// システム設定の保存
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void SceneManager::SaveSystem(const int& mouseNumber)
{
	//	マウス感度番号の更新
	m_systemData[DATA_STR] = mouseNumber;

	//	データの保存
	JsonManager::SaveFile(DataPath::SYSTEM_DATA_PATH, m_systemData);
}