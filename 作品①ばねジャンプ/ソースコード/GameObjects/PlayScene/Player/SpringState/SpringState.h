//--------------------------------------------------------------------------------------
// File: SpringState.h
//
// プレイヤーばね状態クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SPRING_STATE_DEFINED
#define SPRING_STATE_DEFINED

class PlayerSpring;

class SpringState
{
public:
	/// <summary>
	///	コンストラクタ
	/// </summary>
	/// <param name="spring">プレイヤーばねクラスのポインタ</param>
	SpringState(PlayerSpring* spring) :
		m_spring(spring) { }

	/// <summary>
	/// プレイヤーばねクラスの取得
	/// </summary>
	/// <returns>プレイヤーばねクラスのポインタ</returns>
	PlayerSpring* GetSpring() { return m_spring; }

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SpringState() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;

private:
	//	プレイヤーばねクラスのポインタ
	PlayerSpring* m_spring;
};
#endif // !SPRING_STATE_DEFINED