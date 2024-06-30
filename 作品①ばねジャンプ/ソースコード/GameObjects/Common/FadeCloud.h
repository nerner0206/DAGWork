//--------------------------------------------------------------------------------------
// File: FadeCloud.h
//
// フェイド用雲画像クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef FADE_CLOUD_DEFINED
#define FADE_CLOUD_DEFINED

#include "MyLib/UserInterface.h"

/// <summary>
/// フェイド用雲画像クラス
/// </summary>
class FadeCloud
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FadeCloud();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~FadeCloud();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// フェイドイン初期化
	/// </summary>
	void FadeInStart();
	/// <summary>
	/// フェイドイン更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <returns>終了判定</returns>
	bool FadeInUpdate(const float& elapsedTime);

	/// <summary>
	/// フェイドアウト初期化
	/// </summary>
	void FadeOutStart();
	/// <summary>
	/// フェイドアウト更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <returns>終了判定</returns>
	bool FadeOutUpdate(const float& elapsedTime);

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

private:
	//	白い画像の拡大率
	static const float WHITE_SCALE;
	//	移動速度
	static const float MOVE_SPEED;

	//	フェイドイン初期座標
	static const DirectX::SimpleMath::Vector2 FADE_IN_START_POSITION;

private:
	//	雲画像クラスのユニークポインタ
	std::unique_ptr<UserInterface> m_cloud;
	//	白い画像クラスのユニークポインタ
	std::unique_ptr<UserInterface> m_white;
};
#endif // !FADE_CLOUD_DEFINED
