//--------------------------------------------------------------------------------------
// File: SpringStateShrink.cpp
//
// プレイヤーばねの通常状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringStateShrink.h"

#include "SpringStateDefault.h"

using namespace DirectX;

/// <summary>
///	コンストラクタ
/// </summary>
/// <param name="spring">プレイヤーばねクラスのポインタ</param>
SpringStateShrink::SpringStateShrink(PlayerSpring* spring) :
	SpringState(spring)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SpringStateShrink::~SpringStateShrink()
{

}

/// <summary>
/// 初期化
/// </summary>
void SpringStateShrink::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void SpringStateShrink::Update(const float& elapsedTime)
{
	//	拡大率の取得
	SimpleMath::Vector3 sca = GetSpring()->GetSca();

	//	縮小する
	sca.y *= GetSpring()->GetShrinkRatio();

	//	縮み切ったら
	if (sca.y < 0.5f)
	{
		//	サイズを最低値へ戻す
		sca.y = 0.5f;
		//	拡大率の設定
		GetSpring()->SetSca(sca);

		//	縮み中を解除する
		GetSpring()->SetIsShrink(false);

		//	跳ね返る速度
		SimpleMath::Vector3 vel = SimpleMath::Vector3::Transform(
			SimpleMath::Vector3(0.0f, GetSpring()->GetJumpForce(), 0.0f), GetSpring()->GetRotQua());
		//	速度の設定
		GetSpring()->SetVelocity(vel);

		//	ジャンプ音の再生
		GetSpring()->GetAudioResources()->PlayJumpSE();

		//	風船の破壊
		GetSpring()->BreakBalloon();

		//	状態を通常状態へ
		GetSpring()->SetNextState(new SpringStateDefault(GetSpring()));
		return;
	}

	//	速度の取得
	SimpleMath::Vector3 vel = GetSpring()->GetVelocity();
	//	座標の取得
	SimpleMath::Vector3 pos = GetSpring()->GetPos();

	//	重力の加算
	vel.y -= GetSpring()->GetGravity();
	//	速度の加算
	pos += (vel * elapsedTime);

	//	速度の設定
	GetSpring()->SetVelocity(vel);
	//	座標の設定
	GetSpring()->SetPos(pos);
	//	拡大率の設定
	GetSpring()->SetSca(sca);
}

/// <summary>
/// 終了
/// </summary>
void SpringStateShrink::Finalize()
{

}