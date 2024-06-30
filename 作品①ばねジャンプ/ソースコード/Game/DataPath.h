//--------------------------------------------------------------------------------------
// File: DataPath.h
//
// データパスクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef DATA_PATH_DEFINED
#define DATA_PATH_DEFINED

/// <summary>
/// データーパスクラス
/// </summary>
class DataPath
{
public:
	//--------------------------------------------------------------------------------------
	//	jsonパス
	//--------------------------------------------------------------------------------------
	
	//	システムデータのファイルパス
	static const char* SYSTEM_DATA_PATH;


	//	プレイカメラデータのファイルパス
	static const char* PLAY_CAMERA_DATA_PATH;
	//	プレイヤーデータのファイルパス
	static const char* PLAYER_SPRING_DATA_PATH;
	//	ステージ数
	static const int STAGE_NUMBER = 7;
	//	ステージデータのファイルパス
	static const char* STAGE_DATA_PATHs[STAGE_NUMBER];

	//--------------------------------------------------------------------------------------
	//	Shaderパス
	//--------------------------------------------------------------------------------------

	//	大きい雲の頂点シェーダのファイルパス
	static const wchar_t* BIG_CLOUD_VS_PATH;
	//	大きい雲のピクセルシェーダのファイルパス
	static const wchar_t* BIG_CLOUD_PS_PATH;

	//--------------------------------------------------------------------------------------
	//	モデルパス
	//--------------------------------------------------------------------------------------

	//	スカイドームモデルのファイルパス
	static const wchar_t* SKYDOME_MODEL_PATH;
	//	大きい雲モデルのファイルパス
	static const wchar_t* BIG_CLOUD_MODEL_PATH;

	//	タイトルシーン雲モデルのファイルパス
	static const wchar_t* TITLE_CLOUD_MODEL_PATH;
	//	タイトルテキストモデルの数
	static const int TITLE_TEXT_MODEL_NUMBER = 6;
	//	タイトルテキストモデルのファイルパス配列
	static const wchar_t* TITLE_TEXT_MODEL_PATHs[TITLE_TEXT_MODEL_NUMBER];

	//	セレクトシーン雲モデルのファイルパス
	static const wchar_t* SELECT_CLOUD_MODEL_PATH;
	//	セレクトテキストモデルのファイルパス配列
	static const wchar_t* SELECT_TEXT_MODEL_PATHs[STAGE_NUMBER];

	//	プレイヤーばねモデルの数
	static const int PLAYER_SPRING_MODEL_NUMBER = 4;
	//	プレイヤーばねモデルのファイルパス配列
	static const wchar_t* PLAYER_SPRING_MODEL_PATHs[PLAYER_SPRING_MODEL_NUMBER];
	//	プレイヤー頭モデルのファイルパス
	static const wchar_t* PLAYER_HEAD_MODEL_PATH;

	//	雲（ステージオブジェクト）モデルのファイルパス
	static const wchar_t* STAGE_CLOUD_MODEL_PATH;
	//	ゴール（ステージオブジェクト）モデルのファイルパス
	static const wchar_t* STAGE_GOAL_MODEL_PATH;
	//	スタート（ステージオブジェクト）モデルのファイルパス
	static const wchar_t* STAGE_START_MODEL_PATH;
	//	風船（ステージオブジェクト）モデルのファイルパス
	static const wchar_t* STAGE_BALLOON_MODEL_PATH;
	//	飛行機（ステージオブジェクト）モデルのファイルパス
	static const wchar_t* STAGE_PLANE_MODEL_PATH;

	//--------------------------------------------------------------------------------------
	//	ディレクトリパス
	//--------------------------------------------------------------------------------------

	//	モデルフォルダへのディレクトリパス
	static const wchar_t* MODEL_FOLDER_DIRECTORY_PATH;
	//	テキストモデルフォルダへのディレクトリパス
	static const wchar_t* TEXT_MODEL_FOLDER_DIRECTORY_PATH;
	//	プレイヤーモデルファルダへのディレクトリパス
	static const wchar_t* PLAYER_MODEL_FOLDER_DIRECTORY_PATH;
	//	ステージモデルファルダへのディレクトリパス
	static const wchar_t* STAGE_MODEL_FOLDER_DIRECTORY_PATH;

	//--------------------------------------------------------------------------------------
	//	画像パス
	//--------------------------------------------------------------------------------------

	//	フェイド用雲画像のファイルパス
	static const wchar_t* FADE_CLOUD_IMAGE_PATH;
	//	フェイド用白い画像のファイルパス
	static const wchar_t* FADE_WHITE_IMAGE_PATH;

	//	スペース1画像のファイルパス
	static const wchar_t* SPACE01_IMAGE_PATH;
	//	スペース2画像のファイルパス
	static const wchar_t* SPACE02_IMAGE_PATH;

	//	右矢印画像のファイルパス
	static const wchar_t* RIGHT_ARROW_IMAGE_PATH;
	//	左矢印画像のファイルパス
	static const wchar_t* LEFT_ARROW_IMAGE_PATH;

	//	数字画像の数
	static const int NUMBER_IMAGE_NUMBER = 10;
	//	数字画像のファイルパス配列
	static const wchar_t* NUMBER_IMAGE_PATHs[NUMBER_IMAGE_NUMBER];

	//	タイマーの中心記号画像のファイルパス
	static const wchar_t* TIMER_CENTER_IMAGE_PATH;

	//	設定画面の背景画像のファイルパス
	static const wchar_t* SYSTEM_BACK_IMAGE_PATH;
	//	設定画面の選択フレーム画像のファイルパス
	static const wchar_t* SYSTEM_FRAME_IMAGE_PATH;

	//	設定画面の選択肢数
	static const int SYSTEM_SELECT_NUMBER = 4;
	//	設定画面の選択肢画像のファイルパス配列
	static const wchar_t* SYSTEM_SELECT_IMAGE_PATHs[SYSTEM_SELECT_NUMBER];

	//	マウス感度の番号数
	static const int SYSTEM_MOUSE_NUMBER = 5;
	//	設定画面のマウス感度選択フレーム画像のファイルパス
	static const wchar_t* SYSTEM_MOUSE_FRAME_IMAGE_PATH;

	//	セレクトシーンのタイトル画像のファイルパス
	static const wchar_t* SELECT_IMAGE_PATH;

	//	ステージ画像のファイルパス
	static const wchar_t* STAGE_IMAGE_PATH;

	//	ルール画像のファイルパス
	static const wchar_t* RULU_IMAGE_PATH;

	//	カメラ切り替え(操作方法)画像のファイルパス
	static const wchar_t* C_ICON_IMAGE_PATH;
	//	カメラ切り替え(操作方法)画像のファイルパス
	static const wchar_t* C_BUTTON_IMAGE_PATH;
	//	予測線の表示切り替え(操作方法)画像のファイルパス
	static const wchar_t* X_ICON_IMAGE_PATH;
	//	予測線の表示切り替え(操作方法)画像のファイルパス
	static const wchar_t* X_BUTTON_IMAGE_PATH;

	//	黒い円画像のファイルパス
	static const wchar_t* BLACK_CIRCLE_IMAGE_PATH;
	//	赤い円画像のファイルパス
	static const wchar_t* RED_CIRCLE_IMAGE_PATH;
	//	死亡アイコン画像のファイルパス
	static const wchar_t* DEAD_ICON_IMAGE_PATH;
	//	リザルト画像のファイルパス
	static const wchar_t* RESULT_IMAGE_PATH;

	//	雲パーティクル画像のファイルパス
	static const wchar_t* CLOUD_PARTICLE_IMAGE_PATH;
	//	風パーティクル画像のファイルパス
	static const wchar_t* WIND_PARTICLE_IMAGE_PATH;
	//	爆発パーティクル画像の数
	static const int EXPLOSION_PARTICLE_IMAGE_NUM = 10;
	//	爆発パーティクル画像のファイルパス
	static const wchar_t* EXPLOSION_PARTICLE_IMAGE_PATHs[EXPLOSION_PARTICLE_IMAGE_NUM];

	//--------------------------------------------------------------------------------------
	//	音素材パス
	//--------------------------------------------------------------------------------------
	
	//	BGM1のファイルパス
	static const wchar_t* BGM_PATH;
	//	BGM2のファイルパス
	static const wchar_t* PLAY_BGM_PATH;

	//	決定SEのファイルパス
	static const wchar_t* DECIDE_SE_PATH;
	//	矢印SEのファイルパス
	static const wchar_t* ARROW_SE_PATH;
	//	設定SEのファイルパス
	static const wchar_t* SYSTEM_SE_PATH;

	//	ばねSEのファイルパス
	static const wchar_t* SPRING_SE_PATH;
	//	ジャンプSEのファイルパス
	static const wchar_t* JUMP_SE_PATH;
	//	爆発SEのファイルパス
	static const wchar_t* EXPLOSION_SE_PATH;
	//	破裂SEのファイルパス
	static const wchar_t* BALLOON_SE_PATH;
	//	風SEのファイルパス
	static const wchar_t* WIND_SE_PATH;

	//	クラッカー①SEのファイルパス
	static const wchar_t* CRACKER01_SE_PATH;
	//	クラッカー②SEのファイルパス
	static const wchar_t* CRACKER02_SE_PATH;

	//	クリアSEのファイルパス
	static const wchar_t* CREAR_SE_PATH;
	//	死亡SEのファイルパス
	static const wchar_t* DEAD_SE_PATH;
};
#endif // !DATA_PATH_DEFINED