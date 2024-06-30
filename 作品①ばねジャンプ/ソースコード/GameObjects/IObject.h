//--------------------------------------------------------------------------------------
// File: IObject.h
//
// オブジェクトインターフェースのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef IOBJECT_DEFINED
#define IOBJECT_DEFINED

#include "MyLib/UserResources.h"
#include "MyLib/AudioResources.h"
#include "Game/DataPath.h"

/// <summary>
/// オブジェクトインターフェース
/// </summary>
interface IObject
{
	/// <summary>
	/// ユーザーリソースクラスの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	virtual UserResources* GetUserResources() = 0;
	/// <summary>
	/// 音リソースクラスの取得
	/// </summary>
	/// <returns>音リソースクラスのポインタ</returns>
	virtual AudioResources* GetAudioResources() = 0;

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IObject() = default;

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	virtual const DirectX::SimpleMath::Vector3 GetPos() = 0;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	virtual void SetPos(const DirectX::SimpleMath::Vector3& pos) = 0;

	/// <summary>
	/// 回転クォータニオンの取得
	/// </summary>
	/// <returns>回転クォータニオン</returns>
	virtual const DirectX::SimpleMath::Quaternion GetRotQua() = 0;
	/// <summary>
	/// 回転クォータニオンの設定
	/// </summary>
	/// <param name="rotQua">回転クォータニオン</param>
	virtual void SetRotQua(const DirectX::SimpleMath::Quaternion& rotQua) = 0;

	/// <summary>
	/// 拡大率の取得
	/// </summary>
	/// <returns>拡大率</returns>
	virtual const DirectX::SimpleMath::Vector3 GetSca() = 0;
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="sca">拡大率</param>
	virtual void SetSca(const DirectX::SimpleMath::Vector3& sca) = 0;
};
#endif // !IOBJECT_DEFINED
