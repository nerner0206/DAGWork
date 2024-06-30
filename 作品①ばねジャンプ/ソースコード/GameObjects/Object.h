//--------------------------------------------------------------------------------------
// File: Object.h
//
// オブジェクト基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef OBJECT_DEFINED
#define OBJECT_DEFINED

#include "IObject.h"

/// <summary>
/// オブジェクト基底クラス
/// </summary>
class Object : public IObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rotQua">回転クォータニオン</param>
	/// <param name="sca">拡大率</param>
	Object(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Quaternion& rotQua,
		const DirectX::SimpleMath::Vector3& sca) :
		m_pos(pos), m_rotQua(rotQua), m_sca(sca)
	{
		//	ユーザーリソースの取得
		m_ur = UserResources::GetInstance();
		//	音リソースクラスの取得
		m_ar = AudioResources::GetInstance();
	}

	/// <summary>
	/// ユーザーリソースクラスの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	UserResources* GetUserResources() override { return m_ur; }
	/// <summary>
	/// 音リソースクラスの取得
	/// </summary>
	/// <returns>音リソースクラスのポインタ</returns>
	AudioResources* GetAudioResources() override { return m_ar; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const DirectX::SimpleMath::Vector3 GetPos() override { return m_pos; }
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPos(const DirectX::SimpleMath::Vector3& pos) override { m_pos = pos; }

	/// <summary>
	/// 回転クォータニオンの取得
	/// </summary>
	/// <returns>回転クォータニオン</returns>
	const DirectX::SimpleMath::Quaternion GetRotQua() override { return m_rotQua; }
	/// <summary>
	/// 回転クォータニオンの設定
	/// </summary>
	/// <param name="rotQua">回転クォータニオン</param>
	void SetRotQua(const DirectX::SimpleMath::Quaternion& rotQua) override { m_rotQua = rotQua; }

	/// <summary>
	/// 拡大率の取得
	/// </summary>
	/// <returns>拡大率</returns>
	const DirectX::SimpleMath::Vector3 GetSca() override { return m_sca; }
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="sca">拡大率</param>
	void SetSca(const DirectX::SimpleMath::Vector3& sca) override { m_sca = sca; }

public:
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~Object() = default;

private:
	//	ユーザーリソースクラスのポインタ
	UserResources* m_ur;
	//	音リソースクラスのポインタ
	AudioResources* m_ar;

	//	座標
	DirectX::SimpleMath::Vector3 m_pos;
	//	回転クォータニオン
	DirectX::SimpleMath::Quaternion m_rotQua;
	//	拡大率
	DirectX::SimpleMath::Vector3 m_sca;
};
#endif // !OBJECT_DEFINED
