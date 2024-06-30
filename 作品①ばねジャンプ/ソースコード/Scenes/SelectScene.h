//--------------------------------------------------------------------------------------
// File: SelectScene.h
//
// セレクトシーンクラスのヘッダーフェイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SELECT_SCENE_DEFINED
#define SELECT_SCENE_DEFINED

#include "MyLib/IScene.h"

#include <vector>

class TextModel;
class Cloud;

class SpaceUI;

/// <summary>
/// セレクトシーンクラス
/// </summary>
class SelectScene : public IScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectScene();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	void Initialize(const int& mouseNumber) override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// 描画
	/// </summary>
	void Render() override;
	/// <summary>
	/// 影描画
	/// </summary>
	void ShadowRender() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

private:
	//	スカイドームの回転速度
	static const float SKYDOME_ROT_SPEED;

	//	カメラの回転距離定数
	static const float MODEL_DISTANCE;

	//	モデルの座標Y・Z
	static const float MODEL_POS_Y;
	static const float MODEL_POS_Z;

	//	テキストモデルの座標Y
	static const float TEXT_MODEL_POS_Y;

	//	モデルの縮小倍率
	static const float MODEL_MIN_SCALE;

	//	カメラの目標座標定数
	static const DirectX::SimpleMath::Vector3 CAMERA_TARGET_POSITION;

	//	ライトの影響範囲
	static const float LIGHT_RANGE;

	//	スペースUIの高さ
	static const int SPACE_UI_HEIGHT = 600;

	//	タイトル画像の拡大率
	static const float TITLE_IMAGE_SCALE;
	//	矢印画像の間隔
	static const int ARROW_IMAGE_DISTANCE = 300;

private:
	//	文字モデルクラスのユニークポインタ配列
	std::vector<std::unique_ptr<TextModel>> m_textModels;
	//	雲クラスのユニークポインタ配列
	std::vector<std::unique_ptr<Cloud>> m_clouds;

	//	ステージ番号
	int m_stageNum;
	//	以前のステージ番号
	int m_stageBeforeNum;

	//	カメラの現在の座標
	DirectX::SimpleMath::Vector3 m_cameraNowPos;
	//	カメラの次の座標
	DirectX::SimpleMath::Vector3 m_cameraNextPos;

	//	ステージ変更中
	bool isChange;

	//	タイマー
	float m_timer;

	//	セレクトタイトルUIのユニークポインタ
	std::unique_ptr<UserInterface> m_selectTitleUI;
	//	右矢印UIのユニークポインタ
	std::unique_ptr<UserInterface> m_rightArrowUI;
	//	左矢印UIのユニークポインタ
	std::unique_ptr<UserInterface> m_leftArrowUI;
	//	スタートUIクラスのユニークポインタ
	std::unique_ptr<SpaceUI> m_spaceUI;

private:
	/// <summary>
	/// ステージ変更
	/// </summary>
	void ChangeStage();
};
#endif		// SELECT_SCENE_DEFINED