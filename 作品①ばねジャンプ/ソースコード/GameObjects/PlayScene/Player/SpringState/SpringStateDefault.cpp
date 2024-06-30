//--------------------------------------------------------------------------------------
// File: SpringStateDefault.cpp
//
// プレイヤーばねの通常状態クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpringStateDefault.h"

using namespace DirectX;

/// <summary>
///	コンストラクタ
/// </summary>
/// <param name="spring">プレイヤーばねクラスのポインタ</param>
SpringStateDefault::SpringStateDefault(PlayerSpring* spring) :
	SpringState(spring)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SpringStateDefault::~SpringStateDefault()
{

}

/// <summary>
/// 初期化
/// </summary>
void SpringStateDefault::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void SpringStateDefault::Update(const float& elapsedTime)
{
	//	拡大率の取得
	SimpleMath::Vector3 sca = GetSpring()->GetSca();

	//	ばねが縮んでいる
	if (sca.y < 1.0f)
	{
		//	徐々に伸ばす
		sca.y += GetSpring()->GetExtendSpeed();
		if (sca.y > 1.0f) sca.y = 1.0f;
	}

	//	拡大率の設定
	GetSpring()->SetSca(sca);

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
}

/// <summary>
/// 終了
/// </summary>
void SpringStateDefault::Finalize()
{

}