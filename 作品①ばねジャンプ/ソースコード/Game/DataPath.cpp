//--------------------------------------------------------------------------------------
// File: DataPath.cpp
//
// データパスクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DataPath.h"

//--------------------------------------------------------------------------------------
//	jsonパス
//--------------------------------------------------------------------------------------

//	システムデータのファイルパス
const char* DataPath::SYSTEM_DATA_PATH = "Resources/Datas/MouseSetting.json";

//	プレイカメラデータのファイルパス
const char* DataPath::PLAY_CAMERA_DATA_PATH = "Resources/Datas/PlayCamera.json";
//	プレイヤーデータのファイルパス
const char* DataPath::PLAYER_SPRING_DATA_PATH = "Resources/Datas/PlayerSpring.json";

//	ステージデータのファイルパス
const char* DataPath::STAGE_DATA_PATHs[STAGE_NUMBER] =
{
	"Resources/Datas/Stages/Stage01.json",
	"Resources/Datas/Stages/Stage02.json",
	"Resources/Datas/Stages/Stage03.json",
	"Resources/Datas/Stages/Stage04.json",
	"Resources/Datas/Stages/Stage05.json",
	"Resources/Datas/Stages/Stage06.json",
	"Resources/Datas/Stages/Stage07.json"
};

//--------------------------------------------------------------------------------------
//	Shaderパス
//--------------------------------------------------------------------------------------

//	大きい雲の頂点シェーダのファイルパス
const wchar_t* DataPath::BIG_CLOUD_VS_PATH = L"Resources/Shader/cso/Cloud_VS.cso";
//	大きい雲のピクセルシェーダのファイルパス
const wchar_t* DataPath::BIG_CLOUD_PS_PATH = L"Resources/Shader/cso/Cloud_PS.cso";

//--------------------------------------------------------------------------------------
//	モデルパス
//--------------------------------------------------------------------------------------

//	スカイドームモデルのファイルパス
const wchar_t* DataPath::SKYDOME_MODEL_PATH = L"Resources/Models/SkyDome.cmo";
//	大きい雲モデルのファイルパス
const wchar_t* DataPath::BIG_CLOUD_MODEL_PATH = L"Resources/Models/BigCloud.cmo";

//	タイトルシーン雲モデルのファイルパス
const wchar_t* DataPath::TITLE_CLOUD_MODEL_PATH = L"Resources/Models/Clouds/TitleCloud.cmo";
//	タイトルテキストモデルのファイルパス配列
const wchar_t* DataPath::TITLE_TEXT_MODEL_PATHs[TITLE_TEXT_MODEL_NUMBER] =
{
	L"Resources/Models/Texts/Title/ba.cmo",
	L"Resources/Models/Texts/Title/ne.cmo",
	L"Resources/Models/Texts/Title/zi.cmo",
	L"Resources/Models/Texts/Title/ya.cmo",
	L"Resources/Models/Texts/Title/n.cmo",
	L"Resources/Models/Texts/Title/pu.cmo"
};

//	セレクトシーン雲モデルのファイルパス
const wchar_t* DataPath::SELECT_CLOUD_MODEL_PATH = L"Resources/Models/Clouds/SelectCloud.cmo";
//	セレクトテキストモデルのファイルパス配列
const wchar_t* DataPath::SELECT_TEXT_MODEL_PATHs[STAGE_NUMBER] =
{
	L"Resources/Models/Texts/Number/Num_01.cmo",
	L"Resources/Models/Texts/Number/Num_02.cmo",
	L"Resources/Models/Texts/Number/Num_03.cmo",
	L"Resources/Models/Texts/Number/Num_04.cmo",
	L"Resources/Models/Texts/Number/Num_05.cmo",
	L"Resources/Models/Texts/Number/Num_06.cmo",
	L"Resources/Models/Texts/Number/Num_07.cmo"
};

//	プレイヤーばねモデルのファイルパス配列
const wchar_t* DataPath::PLAYER_SPRING_MODEL_PATHs[PLAYER_SPRING_MODEL_NUMBER] =
{
	L"Resources/Models/Player/Spring_01.cmo",
	L"Resources/Models/Player/Spring_02.cmo",
	L"Resources/Models/Player/Spring_03.cmo",
	L"Resources/Models/Player/Spring_04.cmo"
};
//	プレイヤー頭モデルのファイルパス
const wchar_t* DataPath::PLAYER_HEAD_MODEL_PATH = L"Resources/Models/Player/Head.cmo";

//	雲（ステージオブジェクト）モデルのファイルパス
const wchar_t* DataPath::STAGE_CLOUD_MODEL_PATH = L"Resources/Models/Stage/Cloud.cmo";
//	ゴール（ステージオブジェクト）モデルのファイルパス
const wchar_t* DataPath::STAGE_GOAL_MODEL_PATH = L"Resources/Models/Stage/Goal.cmo";
//	スタート（ステージオブジェクト）モデルのファイルパス
const wchar_t* DataPath::STAGE_START_MODEL_PATH = L"Resources/Models/Stage/Start.cmo";
//	風船（ステージオブジェクト）モデルのファイルパス
const wchar_t* DataPath::STAGE_BALLOON_MODEL_PATH = L"Resources/Models/Stage/Balloon.cmo";
//	飛行機（ステージオブジェクト）モデルのファイルパス
const wchar_t* DataPath::STAGE_PLANE_MODEL_PATH = L"Resources/Models/Stage/Plane01.cmo";


//--------------------------------------------------------------------------------------
//	ディレクトリパス
//--------------------------------------------------------------------------------------

//	モデルフォルダへのディレクトリパス
const wchar_t* DataPath::MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models";
//	テキストモデルフォルダへのディレクトリパス
const wchar_t* DataPath::TEXT_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Texts";
//	プレイヤーモデルファルダへのディレクトリパス
const wchar_t* DataPath::PLAYER_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Player";
//	ステージモデルファルダへのディレクトリパス
const wchar_t* DataPath::STAGE_MODEL_FOLDER_DIRECTORY_PATH = L"Resources/Models/Stage";

//--------------------------------------------------------------------------------------
//	画像パス
//--------------------------------------------------------------------------------------

//	フェイド用雲画像のファイルパス
const wchar_t* DataPath::FADE_CLOUD_IMAGE_PATH = L"Resources/Textures/CloudFade.png";
//	フェイド用白い画像のファイルパス
const wchar_t* DataPath::FADE_WHITE_IMAGE_PATH = L"Resources/Textures/White.png";

//	スペース1画像のファイルパス
const wchar_t* DataPath::SPACE01_IMAGE_PATH = L"Resources/Textures/Space.png";
//	スペース2画像のファイルパス
const wchar_t* DataPath::SPACE02_IMAGE_PATH = L"Resources/Textures/SpacePress.png";

//	右矢印画像のファイルパス
const wchar_t* DataPath::RIGHT_ARROW_IMAGE_PATH = L"Resources/Textures/RightArrow.png";
//	左矢印画像のファイルパス
const wchar_t* DataPath::LEFT_ARROW_IMAGE_PATH = L"Resources/Textures/LeftArrow.png";

//	数字画像のファイルパス配列
const wchar_t* DataPath::NUMBER_IMAGE_PATHs[NUMBER_IMAGE_NUMBER] =
{
	L"Resources/Textures/Number/00.png",
	L"Resources/Textures/Number/01.png",
	L"Resources/Textures/Number/02.png",
	L"Resources/Textures/Number/03.png",
	L"Resources/Textures/Number/04.png",
	L"Resources/Textures/Number/05.png",
	L"Resources/Textures/Number/06.png",
	L"Resources/Textures/Number/07.png",
	L"Resources/Textures/Number/08.png",
	L"Resources/Textures/Number/09.png"
};

//	タイマーの中心記号画像のファイルパス
const wchar_t* DataPath::TIMER_CENTER_IMAGE_PATH = L"Resources/Textures/TimeCenter.png";

//	設定画面の背景画像のファイルパス
const wchar_t* DataPath::SYSTEM_BACK_IMAGE_PATH = L"Resources/Textures/System/Back.png";
//	設定画面の選択フレーム画像のファイルパス
const wchar_t* DataPath::SYSTEM_FRAME_IMAGE_PATH = L"Resources/Textures/System/Frame.png";

//	設定画面の選択肢画像のファイルパス配列
const wchar_t* DataPath::SYSTEM_SELECT_IMAGE_PATHs[SYSTEM_SELECT_NUMBER] =
{
	L"Resources/Textures/System/Mouse.png",
	L"Resources/Textures/System/Select.png",
	L"Resources/Textures/System/Title.png",
	L"Resources/Textures/System/Exit.png"
};

//	設定画面のマウス感度選択フレーム画像のファイルパス
const wchar_t* DataPath::SYSTEM_MOUSE_FRAME_IMAGE_PATH = L"Resources/Textures/System/MouseFrame.png";

//	セレクトシーンのタイトル画像のファイルパス
const wchar_t* DataPath::SELECT_IMAGE_PATH = L"Resources/Textures/SelectScene/StageSelect.png";

//	ステージ画像のファイルパス
const wchar_t* DataPath::STAGE_IMAGE_PATH = L"Resources/Textures/PlayScene/Stage.png";

//	ルール画像のファイルパス
const wchar_t* DataPath::RULU_IMAGE_PATH = L"Resources/Textures/PlayScene/Rulu.png";

//	カメラ切り替え(操作方法)画像のファイルパス
const wchar_t* DataPath::C_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/C_Icon.png";
//	カメラ切り替え(操作方法)画像のファイルパス
const wchar_t* DataPath::C_BUTTON_IMAGE_PATH = L"Resources/Textures/PlayScene/C_Button.png";
//	予測線の表示切り替え画像のファイルパス
const wchar_t* DataPath::X_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/X_Icon.png";
//	予測線の表示切り替え(操作方法)画像のファイルパス
const wchar_t* DataPath::X_BUTTON_IMAGE_PATH = L"Resources/Textures/PlayScene/X_Button.png";

//	黒い円画像のファイルパス
const wchar_t* DataPath::BLACK_CIRCLE_IMAGE_PATH = L"Resources/Textures/PlayScene/BlackCircle.png";
//	赤い円画像のファイルパス
const wchar_t* DataPath::RED_CIRCLE_IMAGE_PATH = L"Resources/Textures/PlayScene/RedCircle.png";
//	死亡アイコン画像のファイルパス
const wchar_t* DataPath::DEAD_ICON_IMAGE_PATH = L"Resources/Textures/PlayScene/Skull.png";
//	リザルト画像のファイルパス
const wchar_t* DataPath::RESULT_IMAGE_PATH = L"Resources/Textures/PlayScene/Result.png";

//	雲エフェクト画像のファイルパス
const wchar_t* DataPath::CLOUD_PARTICLE_IMAGE_PATH = L"Resources/Textures/PlayScene/CloudParticle.png";
//	風パーティクル画像のファイルパス
const wchar_t* DataPath::WIND_PARTICLE_IMAGE_PATH = L"Resources/Textures/PlayScene/WindParticle.png";
//	爆発エフェクト画像のファイルパス
const wchar_t* DataPath::EXPLOSION_PARTICLE_IMAGE_PATHs[EXPLOSION_PARTICLE_IMAGE_NUM] =
{
	L"Resources/Textures/PlayScene/Explosion/explosion01.png",
	L"Resources/Textures/PlayScene/Explosion/explosion02.png",
	L"Resources/Textures/PlayScene/Explosion/explosion03.png",
	L"Resources/Textures/PlayScene/Explosion/explosion04.png",
	L"Resources/Textures/PlayScene/Explosion/explosion05.png",
	L"Resources/Textures/PlayScene/Explosion/explosion06.png",
	L"Resources/Textures/PlayScene/Explosion/explosion07.png",
	L"Resources/Textures/PlayScene/Explosion/explosion08.png",
	L"Resources/Textures/PlayScene/Explosion/explosion09.png",
	L"Resources/Textures/PlayScene/Explosion/explosion10.png"
};

//--------------------------------------------------------------------------------------
//	音素材パス
//--------------------------------------------------------------------------------------

//	BGM1のファイルパス
const wchar_t* DataPath::BGM_PATH = L"Resources/Audios/BGM_01.wav";
//	BGM2のファイルパス
const wchar_t* DataPath::PLAY_BGM_PATH = L"Resources/Audios/BGM_02.wav";

//	決定SEのファイルパス
const wchar_t* DataPath::DECIDE_SE_PATH = L"Resources/Audios/Decide.wav";
//	矢印SEのファイルパス
const wchar_t* DataPath::ARROW_SE_PATH = L"Resources/Audios/Arrow.wav";
//	設定SEのファイルパス
const wchar_t* DataPath::SYSTEM_SE_PATH = L"Resources/Audios/SystemWindow.wav";

//	ばねSEのファイルパス
const wchar_t* DataPath::SPRING_SE_PATH = L"Resources/Audios/Spring.wav";
//	ジャンプSEのファイルパス
const wchar_t* DataPath::JUMP_SE_PATH = L"Resources/Audios/Jump.wav";
//	爆発SEのファイルパス
const wchar_t* DataPath::EXPLOSION_SE_PATH = L"Resources/Audios/Explosion.wav";
//	破裂SEのファイルパス
const wchar_t* DataPath::BALLOON_SE_PATH = L"Resources/Audios/BalloonBreak.wav";
//	風SEのファイルパス
const wchar_t* DataPath::WIND_SE_PATH = L"Resources/Audios/Wind.wav";

//	クラッカー①SEのファイルパス
const wchar_t* DataPath::CRACKER01_SE_PATH = L"Resources/Audios/Cracker01.wav";
//	クラッカー②SEのファイルパス
const wchar_t* DataPath::CRACKER02_SE_PATH = L"Resources/Audios/Cracker02.wav";

//	クリアSEのファイルパス
const wchar_t* DataPath::CREAR_SE_PATH = L"Resources/Audios/Clear.wav";
//	死亡SEのファイルパス
const wchar_t* DataPath::DEAD_SE_PATH = L"Resources/Audios/Dead.wav";