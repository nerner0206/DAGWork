//--------------------------------------------------------------------------------------
// File: PlayScene.cpp
//
// プレイシーンクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayScene.h"

#include "Scenes/SelectScene.h"

#include "Scenes/PlayScene/StartBefore.h"

#include "GameObjects/PlayScene/Player/Player.h"
#include "GameObjects/PlayScene/StageObjects/StageManager.h"

#include "GameObjects/PlayScene/Camera/PlayCamera.h"
#include "GameObjects/PlayScene/Camera/DebugCamera.h"

#include "GameObjects/PlayScene/Particle/Particle.h"
#include "GameObjects/Common/BigCloud.h"

#include "imgui.h"

using namespace DirectX;

//	ライトの座標
const SimpleMath::Vector3 PlayScene::LIGHT_POSITION = SimpleMath::Vector3(15.0f, 30.0f, 15.0f);
//	ライトの影響範囲
const float PlayScene::LIGHT_RANGE = 100.0f;

//	大きい雲の座標
const SimpleMath::Vector3 PlayScene::BIG_CLOUD_POSITION = SimpleMath::Vector3(0.0f, -5.0f, 0.0f);
//	大きい雲の拡大率
const float PlayScene::BIG_CLOUD_SCALE = 10.0f;

//	ステージ番号UIの拡大率
const float PlayScene::STAGE_NUMBER_SCALE = 0.8f;

//	スペースUIの座標
const SimpleMath::Vector2 PlayScene::SPACE_POSITION = SimpleMath::Vector2(640, 650);
//	時間UIの座標
const SimpleMath::Vector2 PlayScene::COUNTER_POSITION = SimpleMath::Vector2(1170, 40);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="num">ステージ番号</param>
PlayScene::PlayScene(const int& stageNum):
	IScene(IScene::SceneKind::PlayScene),
	m_nowState(nullptr),
	m_nextState(nullptr),
	m_stageNum(stageNum),
	m_mode(PlaySceneMode::PlayMode)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void PlayScene::Initialize(const int& mouseNumber)
{
	// 射影行列の作成
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f);
	//	射影行列を設定する
	SetProjMatrix(proj);

	//	ステージ管理クラスの生成
	m_stageManager = std::make_unique<StageManager>();
	//	プレイヤーの生成
	m_player = std::make_unique<Player>();

	//	ステージの初期化
	m_stageManager->Initialize(m_stageNum, m_player.get());

	//	プレイヤーの初期化
	SimpleMath::Vector3 startPos = m_stageManager->GetStartPosition();

	//	プレイカメラの生成
	m_playCamera = std::make_unique<PlayCamera>(startPos, m_stageManager->GetGoal()->GetPos());
	//	デバックカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>();

	//	プレイヤーの初期化
	m_player->Initialize(startPos);

	//	大きい雲クラスの生成
	m_bigCloud = std::make_unique<BigCloud>(this);
	m_bigCloud->Initialize(BIG_CLOUD_POSITION, BIG_CLOUD_SCALE);

	//	パーティクルの設定
	AddParticle(m_player->GetJumpParticle());
	AddParticle(m_player->GetExplosionParticle());

	//	プレイヤーの座標の取得
	SimpleMath::Vector3 p_pos = m_player->GetPlayerSpring()->GetPos();

	// ライトの位置を設定
	SetLightPos(p_pos + LIGHT_POSITION);
	// ライトのターゲットの位置を設定
	SetLightTarget(p_pos);
	// ライトの影響範囲を設定
	SetLightRange(LIGHT_RANGE);

	//	マウス感度の設定
	SetMouseSpeed(mouseNumber);

	//	UIの生成
	CreateUI();
	//	入力前状態の生成
	SetState(new StartBefore(this, m_playCamera.get()));

	//	BGMの再生
	GetAudioResources()->PlayBGM2();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void PlayScene::Update(const float& elapsedTime)
{
	//	キーボードの取得
	auto key = Keyboard::Get().GetState();

	switch (m_mode)
	{
	//	プレイモード
	case PlaySceneMode::PlayMode:			
		//	モード切替(ctrl+D)
		if (key.LeftControl && key.D)
		{
			//	デバッグモードへ
			m_mode = PlaySceneMode::DebugMode;
			//	マウスカーソルの表示
			ShowCursor(true);

			//	処理終了
			return;
		}

		//	次の状態が存在する
		if (m_nextState)
		{
			//	次の状態の設定
			SetState(m_nextState);
			//	次の状態の削除
			m_nextState = nullptr;
		}

		//	状態の更新
		if (m_nowState) m_nowState->Update(elapsedTime, m_player.get(), m_stageManager.get());

		//	カメラ座標の取得
		SetCameraPos(m_playCamera->GetPos());
		//	カメラ目標座標の取得
		SetCameraTarget(m_playCamera->GetTargetPosition());
		break;

	//	デバッグモード
	case PlaySceneMode::DebugMode:			
		//	モード切替(ctrl+S)
		if (key.LeftControl && key.S)
		{
			//	プレイモードへ
			m_mode = PlaySceneMode::PlayMode;
			//	マウスカーソルの削除
			ShowCursor(false);
			//	データの保存
			SaveData();

			//	リセット
			m_player->Reset();
			m_stageManager->Reset();
			return;
		}

		//	デバックカメラの更新処理
		m_debugCamera->Update();

		//	カメラ座標の取得
		SetCameraPos(m_debugCamera->GetPos());
		//	カメラ目標座標の取得
		SetCameraTarget(m_debugCamera->GetTargetPosition());
		break;
	}

	//	パーティクルの更新
	for (auto& particle : m_particles)
	{
		if (particle->GetActive()) particle->Update(elapsedTime);
	}

	//	プレイヤーの座標の取得
	SimpleMath::Vector3 p_pos = m_player->GetPlayerSpring()->GetPos();
	// ライトの位置を設定
	SetLightPos(p_pos + LIGHT_POSITION);
	// ライトのターゲットの位置を設定
	SetLightTarget(p_pos);
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Render()
{
	//	プレイカメラからビュー行列の取得
	if(m_mode == PlaySceneMode::PlayMode) SetViewMatrix(m_playCamera->GetViewMatrix());
	//	デバッグカメラからビュー行列の取得
	else SetViewMatrix(m_debugCamera->GetViewMatrix());

	//	スカイドームの描画
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());
	//	大きい雲の描画
	m_bigCloud->Render(GetViewMatrix(), GetProjMatrix());

	//	ステージ管理クラスの描画
	m_stageManager->Render(GetViewMatrix(), GetProjMatrix());
	//	プレイヤーの描画
	m_player->Render(GetViewMatrix(), GetProjMatrix());

	//	パーティクルの描画
	for (auto& particle : m_particles)
	{
		if (particle->GetActive()) particle->Render(GetViewMatrix(), GetProjMatrix());
	}

	//	UIの描画
	m_stageUI->Render();
	m_stageNumUI->Render();

	switch (m_mode)
	{
	//	プレイモード
	case PlaySceneMode::PlayMode:
		//	状態の描画
		if (m_nowState) m_nowState->Render(GetViewMatrix(), GetProjMatrix());
		break;

	//	デバッグモード
	case PlaySceneMode::DebugMode:
		//	プレイカメラのデバッグ描画
		m_playCamera->DebugRender(GetViewMatrix(), GetProjMatrix());
		//	プレイヤーのデバッグ描画
		m_player->DebugRender();
		//	ステージ管理クラスのデバッグ描画
		m_stageManager->DebugRender();
		break;
	}
}

/// <summary>
/// 影描画
/// </summary>
void PlayScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view, proj;

	//----- シャドウマップの作成 -----//
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	プレイヤーの影をシャドウマップへ描画
			m_player->ShadowRender(view, proj);
			//	ステージオブジェクトへの影の描画
			m_stageManager->ShadowRender(view, proj);
		}
	);
}

/// <summary>
/// 終了
/// </summary>
void PlayScene::Finalize()
{
	//	BGMの停止
	GetAudioResources()->StopBGM2();

	//	現在のプレイシーン状態を削除
	DeletePlaySceneState();

	m_player->Finalize();
	m_stageManager->Finalize();
	m_bigCloud->Finalize();
}

/// <summary>
/// プレイシーン状態の設定
/// </summary>
/// <param name="state">プレイシーン状態クラスのポインタ</param>
void PlayScene::SetState(IPlaySceneState* state)
{
	// シーンを削除
	DeletePlaySceneState();

	// シーンを生成
	m_nowState = state;

	// シーンの初期化処理
	m_nowState->Initialize(m_player.get(), m_stageManager.get());
}

/// <summary>
/// 次のプレイシーン状態の設定
/// </summary>
/// <param name="state">プレイシーン状態クラスのポインタ</param>
void PlayScene::SetNextState(IPlaySceneState* state)
{
	if (m_nextState) return;

	// シーンを生成
	m_nextState = state;
}
/// <summary>
/// プレイシーン状態の削除
/// </summary>
void PlayScene::DeletePlaySceneState()
{
	//	現在のシーンが無ければ処理しない
	if (!m_nowState) return;

	//	シーンの終了処理
	m_nowState->Finalize();
	//	シーンの削除
	delete m_nowState;
	//	nullptrを格納
	m_nowState = nullptr;
}

/// <summary>
/// UIの生成
/// </summary>
void PlayScene::CreateUI()
{
	//	ステージUIの生成
	m_stageUI = std::make_unique<UserInterface>();
	m_stageUI->Create(
		DataPath::STAGE_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH - STAGE_DISTANCE, UserResources::WINDOW_HEIGHT),
		SimpleMath::Vector2::One,
		ANCHOR::BOTTOM_RIGHT);

	//	ステージ番号UIの生成
	m_stageNumUI = std::make_unique<UserInterface>();
	m_stageNumUI->Create(
		DataPath::NUMBER_IMAGE_PATHs[m_stageNum + 1],
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH, UserResources::WINDOW_HEIGHT),
		SimpleMath::Vector2::One * STAGE_NUMBER_SCALE,
		ANCHOR::BOTTOM_RIGHT);
}

/// <summary>
/// マウス感度の設定
/// </summary>
/// <param name="num">マウス感度</param>
void PlayScene::SetMouseSpeed(const int& mouseNumber)
{
	//	マウス感度の計算
	float sensitivity = (float)(mouseNumber + 1) / (float)DataPath::SYSTEM_MOUSE_NUMBER;

	//	マウス感度の設定
	m_player->SetMouseSensitivity(sensitivity);
}

/// <summary>
/// データの保存
/// </summary>
void PlayScene::SaveData()
{
	//	プレイカメラの保存
	m_playCamera->SaveData();
	//	プレイヤーの保存
	m_player->SaveData();
	//	ステージの保存
	m_stageManager->SaveData(m_stageNum);
}