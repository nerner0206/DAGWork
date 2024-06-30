//--------------------------------------------------------------------------------------
// File: TitleScene.h
//
// タイトルシーンクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef TITLE_SCENE_DEFINED
#define TITLE_SCENE_DEFINED

#include "MyLib/IScene.h"

class TitleTextModels;
class Cloud;
class BigCloud;

class SpaceUI;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public IScene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	///	初期化
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
	//	ライトの座標
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	//	ライトの影響範囲
	static const float LIGHT_RANGE;

	//	カメラの座標
	static const DirectX::SimpleMath::Vector3 CAMERA_POSITION;

	//	雲の座標
	static const DirectX::SimpleMath::Vector3 CLOUD_POSITION;

	//	大きい雲の座標
	static const DirectX::SimpleMath::Vector3 BIG_CLOUD_POSITION;
	//	大きい雲の拡大率
	static const float BIG_CLOUD_SCALE;

	//	スカイドームの回転速度
	static const float ROT_SPEED;

	//	スペースUIの座標
	static const DirectX::SimpleMath::Vector2 SPACE_UI_POSITION;

private:
	//	テキストモデル管理クラスのユニークポインタ
	std::unique_ptr<TitleTextModels> m_titleTextModel;
	//	雲クラスのユニークポインタ
	std::unique_ptr<Cloud> m_cloud;
	//	大きな雲クラスのユニークポインタ
	std::unique_ptr<BigCloud> m_bigCloud;

	//	スタートUIクラスのユニークポインタ
	std::unique_ptr<SpaceUI> m_spaceUI;
};
#endif		// TITLE_SCENE_DEFINED