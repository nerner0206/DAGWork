//--------------------------------------------------------------------------------------
// File: TitleTextModel.h
//
// タイトルの文字モデル管理クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef TITLE_TEXT_MODEL_DEFINED
#define TITLE_TEXT_MODEL_DEFINED

#include "GameObjects/Common/TextModel.h"

#include <vector>

/// <summary>
/// タイトルの文字モデル管理クラス
/// </summary>
class TitleTextModels
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleTextModels();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleTextModels();

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
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

private:
	//	初期座標
	static const DirectX::SimpleMath::Vector3 INIT_DEF_POSITION;
	//	座標の間隔
	static const float INIT_SPACE;

	//	縮む速度
	static const float SHRINK_SPEED;
	//	伸びる速度
	static const float EXTEND_SPEED;

	//	拡大率の下限
	static const float MIN_SCALE;
	//	拡大率のデフォルト
	static const float DEF_SCALE;

	//	ジャンプ力
	static const float JUMP_POWER;
	//	重力加速度
	static const float GRAVITY_SCALE;

private:
	//	モデルクラスのユニークポインタ配列
	std::vector<std::unique_ptr<TextModel>> m_textModels;

	//	ジャンプフラグ配列
	std::vector<bool> m_isJumps;
	//	速度配列
	std::vector<DirectX::SimpleMath::Vector3> m_velocities;	
};
#endif // !TITLE_TEXT_MODEL_DEFINED