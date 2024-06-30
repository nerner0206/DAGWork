//--------------------------------------------------------------------------------------
// File: TitleScene.cpp
//
// タイトルシーンクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TitleScene.h"

#include "Scenes/SelectScene.h"

#include "GameObjects/TitleScene/TitleTextModels.h"
#include "GameObjects/Common/Cloud.h"
#include "GameObjects/Common/BigCloud.h"

#include "GameObjects/Common/UI/SpaceUI.h"

#include "MyLib/AudioResources.h"

using namespace DirectX;

//	ライトの座標
const SimpleMath::Vector3 TitleScene::LIGHT_POSITION = SimpleMath::Vector3(0.0f, 30.0f, 15.0f);
//	ライトの影響範囲
const float TitleScene::LIGHT_RANGE = 100.0f;

//	カメラの座標
const SimpleMath::Vector3 TitleScene::CAMERA_POSITION = SimpleMath::Vector3(-2.0f, 2.0f, 5.0f);

//	雲の座標
const SimpleMath::Vector3 TitleScene::CLOUD_POSITION = SimpleMath::Vector3(0.0f, -0.15f, -1.0f);

//	大きい雲の座標
const SimpleMath::Vector3 TitleScene::BIG_CLOUD_POSITION = SimpleMath::Vector3(0.0f, -5.0f, 0.0f);
//	大きい雲の拡大率
const float TitleScene::BIG_CLOUD_SCALE = 10.0f;

//	スカイドームの回転速度
const float TitleScene::ROT_SPEED = 0.02f;

//	スペースUIの座標
const SimpleMath::Vector2 TitleScene::SPACE_UI_POSITION = SimpleMath::Vector2(1030, 600);

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene() :
	IScene(IScene::SceneKind::TitleScene)
{

}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() 
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void TitleScene::Initialize(const int& mouseNumber)
{
	// 射影行列の作成
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f
	);
	//	射影行列の設定
	SetProjMatrix(proj);

	// ライトの座標の設定
	SetLightPos(LIGHT_POSITION);
	// ライトの目標座標の設定
	SetLightTarget(SimpleMath::Vector3::Zero);
	// ライトの影響範囲の設定
	SetLightRange(LIGHT_RANGE);

	//	カメラの座標の設定
	SetCameraPos(CAMERA_POSITION);
	//	カメラの目標座標の設定
	SetCameraTarget(SimpleMath::Vector3::Zero);

	//	ビュー行列の作成
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		GetCameraPos(),
		GetCameraTarget(),
		SimpleMath::Vector3::Up);
	//	ビュー行列の設定
	SetViewMatrix(view);

	//	雲クラスの生成
	m_cloud = std::make_unique<Cloud>();
	m_cloud->Initialize(DataPath::TITLE_CLOUD_MODEL_PATH);
	//	雲の座標の設定
	m_cloud->SetPos(CLOUD_POSITION);

	//	タイトル文字モデルの生成
	m_titleTextModel = std::make_unique<TitleTextModels>();
	m_titleTextModel->Initialize();

	//	大きい雲クラスの生成
	m_bigCloud = std::make_unique<BigCloud>(this);
	m_bigCloud->Initialize(BIG_CLOUD_POSITION, BIG_CLOUD_SCALE);

	//	UIの作成
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(SPACE_UI_POSITION);

	//	BGMの再生
	GetAudioResources()->PlayBGM1();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void TitleScene::Update(const float& elapsedTime)
{
	//	スカイドームの回転
	GetSkyDome()->RotUpdate(ROT_SPEED);

	//	キーボードを設定
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	モデルの更新
	m_titleTextModel->Update(elapsedTime);

	//	スペースを押したらセレクトシーンへ
	if (kbTracker->pressed.Space && GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
		//	決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	セレクトシーンへ
		GetSceneManager()->SetNextScene(new SelectScene());
		//	処理しない
		return;
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Render()
{
	//	スカイドームの描画
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());
	//	大きい雲の描画
	m_bigCloud->Render(GetViewMatrix(), GetProjMatrix());

	//	雲の描画
	m_cloud->Render(GetViewMatrix(), GetProjMatrix());
	//	テキストモデルの描画
	m_titleTextModel->Render(GetViewMatrix(), GetProjMatrix());

	//	UIの描画
	m_spaceUI->Render();
}

/// <summary>
/// 影描画
/// </summary>
void TitleScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix proj = SimpleMath::Matrix::Identity;

	//	シャドウマップの作成
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	テキストモデルの描画
			m_titleTextModel->ShadowRender(view, proj);
			//	雲の描画
			m_cloud->ShadowRender(view, proj);
		}
	);
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	//	BGMの停止
	GetAudioResources()->StopBGM1();

	m_titleTextModel->Finalize();
	m_cloud->Finalize();
	m_bigCloud->Finalize();
}