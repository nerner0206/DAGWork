//--------------------------------------------------------------------------------------
// File: SelectScene.cpp
//
// セレクトシーンクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SelectScene.h"

#include "Scenes/TitleScene.h"
#include "Scenes/PlayScene.h"

#include "GameObjects/Common/TextModel.h"
#include "GameObjects/Common/Cloud.h"

#include "GameObjects/Common/UI/SpaceUI.h"

#include "MyLib/AudioResources.h"

using namespace DirectX;

//	スカイドームの回転速度
const float SelectScene::SKYDOME_ROT_SPEED = 0.02f;

//	モデル間の距離
const float SelectScene::MODEL_DISTANCE = 5.0f;
//	モデルの座標Y・Z
const float SelectScene::MODEL_POS_Y = -1.0f;
const float SelectScene::MODEL_POS_Z = -10.0f;
//	テキストモデルの座標Y
const float SelectScene::TEXT_MODEL_POS_Y = 0.3f;
//	モデルの縮小倍率
const float SelectScene::MODEL_MIN_SCALE = 0.5f;

//	カメラの目標座標
const SimpleMath::Vector3 SelectScene::CAMERA_TARGET_POSITION = SimpleMath::Vector3(0.0f, 0.0f, -10.0f);
//	ライトの影響範囲
const float SelectScene::LIGHT_RANGE = 20.0f;

//	タイトル画像の拡大率
const float SelectScene::TITLE_IMAGE_SCALE = 0.8f;

/// <summary>
/// コンストラクタ
/// </summary>
SelectScene::SelectScene():
	IScene(IScene::SceneKind::SelectScene),
	m_stageNum(0),
	m_stageBeforeNum(0),
	isChange(false),
	m_timer(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SelectScene::~SelectScene()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="mouseNumber">マウス感度番号</param>
void SelectScene::Initialize(const int& mouseNumber)
{
	// 射影行列を作成
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 500.0f
	);
	//	射影行列を設定留守
	SetProjMatrix(proj);

	//	X座標の開始位置
	float startPosX = -DataPath::STAGE_NUMBER / 2 * MODEL_DISTANCE;

	//	カメラの座標を設定する
	SetCameraPos(SimpleMath::Vector3(startPosX, 0.0f, 0.0f));
	//	カメラの目標座標を設定する
	SetCameraTarget(GetCameraPos() + CAMERA_TARGET_POSITION);

	// ライトの位置を設定
	SetLightPos(GetCameraPos());
	// ライトの目標座標を設定
	SetLightTarget(GetCameraTarget());
	// ライトの影響範囲を設定
	SetLightRange(LIGHT_RANGE);

	//	雲とテキスト
	for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
	{
		//	座標の算出
		SimpleMath::Vector3 pos = SimpleMath::Vector3(startPosX, MODEL_POS_Y, MODEL_POS_Z);
		pos.x += (i * MODEL_DISTANCE);

		//	作成
		std::unique_ptr<Cloud> cloud = std::make_unique<Cloud>();
		//	初期化
		cloud->Initialize(DataPath::SELECT_CLOUD_MODEL_PATH);
		//	座標を設定
		cloud->SetPos(pos);

		//	サイズを変更
		if (i == m_stageNum) cloud->SetSca(SimpleMath::Vector3::One);
		else cloud->SetSca(SimpleMath::Vector3::One * MODEL_MIN_SCALE);

		//	配列に渡す
		m_clouds.push_back(std::move(cloud));

		//	テキストモデルの作成
		std::unique_ptr<TextModel> text = std::make_unique<TextModel>();
		//	初期化
		text->Initialize(DataPath::SELECT_TEXT_MODEL_PATHs[i]);
		//	座標を設定
		text->SetPos(pos + SimpleMath::Vector3::UnitY * TEXT_MODEL_POS_Y);

		//	拡大率の変更
		if (i == m_stageNum) text->SetSca(SimpleMath::Vector3::One); 
		else text->SetSca(SimpleMath::Vector3::One * MODEL_MIN_SCALE);

		//	配列に渡す
		m_textModels.push_back(std::move(text));
	}

	//	セレクトタイトルUIの生成
	m_selectTitleUI = std::make_unique<UserInterface>();
	m_selectTitleUI->Create(
		DataPath::SELECT_IMAGE_PATH,
		SimpleMath::Vector2::Zero,
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::TOP_LEFT);

	//	スペースUIの生成
	m_spaceUI = std::make_unique<SpaceUI>();
	m_spaceUI->Initialize(
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2, SPACE_UI_HEIGHT));

	//	右矢印の生成
	m_rightArrowUI = std::make_unique<UserInterface>();
	m_rightArrowUI->Create(
		DataPath::RIGHT_ARROW_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2 + ARROW_IMAGE_DISTANCE, SPACE_UI_HEIGHT),
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::MIDDLE_CENTER);

	//	左矢印の生成
	m_leftArrowUI = std::make_unique<UserInterface>();
	m_leftArrowUI->Create(
		DataPath::LEFT_ARROW_IMAGE_PATH,
		SimpleMath::Vector2(UserResources::WINDOW_WIDTH / 2 - ARROW_IMAGE_DISTANCE, SPACE_UI_HEIGHT),
		SimpleMath::Vector2::One * TITLE_IMAGE_SCALE,
		ANCHOR::MIDDLE_CENTER);

	//	BGMの再生
	GetAudioResources()->PlayBGM1();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void SelectScene::Update(const float& elapsedTime)
{
	//	スカイドームの回転
	GetSkyDome()->RotUpdate(SKYDOME_ROT_SPEED);

	//	変更中
	if (isChange)
	{
		//	時間を増加する
		m_timer += elapsedTime;

		//	1秒後経過
		if (m_timer >= 1.0f)
		{
			//	移動の終了
			isChange = false;
			//	1.0に整える
			m_timer = 1.0f;
		}

		//	拡大率を徐々に大きくする
		SimpleMath::Vector3 sca = SimpleMath::Vector3::Lerp(
			SimpleMath::Vector3::One * MODEL_MIN_SCALE,
			SimpleMath::Vector3::One,
			m_timer);

		//	拡大率の設定
		m_clouds[m_stageNum]->SetSca(sca);
		m_textModels[m_stageNum]->SetSca(sca);

		sca = SimpleMath::Vector3::Lerp(
			SimpleMath::Vector3::One,
			SimpleMath::Vector3::One * MODEL_MIN_SCALE,
			m_timer);

		//	拡大率の設定
		m_clouds[m_stageBeforeNum]->SetSca(sca);
		m_textModels[m_stageBeforeNum]->SetSca(sca);

		//	目標座標を徐々に近づく
		SimpleMath::Vector3 pos = SimpleMath::Vector3::Lerp(
			m_cameraNowPos,
			m_cameraNextPos,
			m_timer);

		//	カメラの座標を設定
		SetCameraPos(pos);
		//	カメラの目標座標を設定する
		SetCameraTarget(pos + CAMERA_TARGET_POSITION);

		// ライトの位置を設定
		SetLightPos(GetCameraPos());
		// ライトの目標座標を設定
		SetLightTarget(GetCameraTarget());

		return;
	}

	//	キーボードトラッカーを取得
	Keyboard::KeyboardStateTracker* kbTracker = GetUserResources()->GetKeyboardStateTracker();

	//	スペースを押したらプレイシーンへ
	if (kbTracker->pressed.Space && GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main)
	{
		//	決定音の再生
		GetAudioResources()->PlayDecideSE();
		//	セレクトシーンへ
		GetSceneManager()->SetNextScene(new PlayScene(m_stageNum));
		//	処理しない
		return;
	}

	//	次のステージ
	if (kbTracker->pressed.Right &&
		GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main &&
		m_stageNum != DataPath::STAGE_NUMBER - 1)
	{
		//	以前の番号を保存
		m_stageBeforeNum = m_stageNum;
		//	次の番号へ
		m_stageNum++;

		//	変更
		ChangeStage();
	}
	//	前のステージ
	else if (kbTracker->pressed.Left &&
		GetSceneManager()->GetSceneState() == SceneManager::SceneState::Main &&
		m_stageNum != 0)
	{
		//	以前の番号を保存
		m_stageBeforeNum = m_stageNum;
		//	前の番号へ
		m_stageNum--;

		//	変更
		ChangeStage();
	}
}

/// <summary>
/// 描画
/// </summary>
void SelectScene::Render()
{
	//	ビュー行列の作成
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		GetCameraPos(),
		GetCameraTarget(),
		SimpleMath::Vector3::Up
	);
	//	ビュー行列の設定
	SetViewMatrix(view);

	//	スカイドーム
	GetSkyDome()->Render(GetViewMatrix(), GetProjMatrix());

	//	雲とテキスト
	for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
	{
		//	モデルの描画
		m_textModels[i]->Render(GetViewMatrix(), GetProjMatrix());
		//	雲の描画
		m_clouds[i]->Render(GetViewMatrix(), GetProjMatrix());
	}

	//	セレクトタイトルUIの描画
	m_selectTitleUI->Render();

	//	スペースUIの描画
	m_spaceUI->Render();

	//	右矢印の描画
	if (m_stageNum != DataPath::STAGE_NUMBER - 1) m_rightArrowUI->Render();
	//	左矢印の描画
	if (m_stageNum != 0) m_leftArrowUI->Render();
}

/// <summary>
/// 影描画
/// </summary>
void SelectScene::ShadowRender()
{
	auto shadowMap = GetUserResources()->GetShadowMap();
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	SimpleMath::Matrix view = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix proj = SimpleMath::Matrix::Identity;

	//----- シャドウマップの作成 -----//
	shadowMap->CreateShadowMap(context, *states, GetLightPos(), GetLightTarget(), GetLightRange(),
		GetCameraPos(), GetCameraTarget(), [&]()
		{
			//	雲とテキスト
			for (int i = 0; i < DataPath::STAGE_NUMBER; i++)
			{
				//	モデルの描画
				m_textModels[i]->ShadowRender(GetViewMatrix(), GetProjMatrix());
				//	雲の描画
				m_clouds[i]->ShadowRender(GetViewMatrix(), GetProjMatrix());
			}
		}
	);
}

/// <summary>
/// 終了
/// </summary>
void SelectScene::Finalize()
{
	//	BGMの停止
	GetAudioResources()->StopBGM1();

	//	雲の描画
	for (auto& cloud : m_clouds)
	{
		cloud->Finalize();
	}
	//	雲の描画
	for (auto& text : m_textModels)
	{
		text->Finalize();
	}
}

/// <summary>
/// ステージ変更
/// </summary>
void SelectScene::ChangeStage()
{
	//	選択音の再生
	GetAudioResources()->PlaySelectSE();

	//	現在の座標
	m_cameraNowPos = GetCameraPos();
	//	次の座標
	m_cameraNextPos = SimpleMath::Vector3(
		m_clouds[m_stageNum]->GetPos().x, 0.0f, 0.0f);

	//	変更中
	isChange = true;
	//	時間をリセット
	m_timer = 0.0f;
}