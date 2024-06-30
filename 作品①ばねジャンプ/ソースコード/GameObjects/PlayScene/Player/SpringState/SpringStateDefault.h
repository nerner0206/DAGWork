//--------------------------------------------------------------------------------------
// File: SpringStateDefault.h
//
// プレイヤーばねの通常状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPRING_STATE_DEFAULT_DEFINED
#define SPRING_STATE_DEFAULT_DEFINED

#include "GameObjects/PlayScene/Player/PlayerSpring.h"

class SpringStateDefault : public SpringState
{
public:
	/// <summary>
	///	コンストラクタ
	/// </summary>
	/// <param name="spring">プレイヤーばねクラスのポインタ</param>
	SpringStateDefault(PlayerSpring* spring);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpringStateDefault();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;
};
#endif // !SPRING_STATE_DEFAULT_DEFINED