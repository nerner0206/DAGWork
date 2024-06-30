//--------------------------------------------------------------------------------------
// File: IStageObject.h
//
// ステージオブジェクト基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISTAGE_OBJECT_DEFINED
#define ISTAGE_OBJECT_DEFINED

#include "GameObjects/Object.h"
#include "GameObjects/PlayScene/CollisionObjects/CollisionObject.h"

#include "imgui.h"

#include <vector>

//	ステージオブジェクト種類
enum class StageObjType
{
	Goal = 0,		//	ゴール
	Cloud,			//	雲
	MoveCloud,		//	動く雲
	Wind,			//	風
	Balloon,		//	風船

	OverID
};

/// <summary>
/// ステージオブジェクト基底クラス
/// </summary>
class IStageObject : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">ステージオブジェクト種類</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転ベクトル</param>
	/// <param name="sca">拡大率</param>
	IStageObject(
		const StageObjType& type,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& rot,
		const DirectX::SimpleMath::Vector3& sca) :
		Object(pos, CalculationRot(rot), sca),
		m_type(type),
		m_isHitActive(true),
		m_collision(nullptr)
	{

	}

	/// <summary>
	/// 回転ベクトルの取得
	/// </summary>
	/// <returns>回転ベクトル</returns>
	const DirectX::SimpleMath::Vector3 GetRot() { return m_rotVec; }
	/// <summary>
	/// 回転ベクトルの設定
	/// </summary>
	/// <param name="rot">回転ベクトル</param>
	void SetRot(const DirectX::SimpleMath::Vector3& rotVec) { m_rotVec = rotVec; }

	/// <summary>
	/// ステージオブジェクト種類の取得
	/// </summary>
	/// <returns>ステージオブジェクト種類</returns>
	const StageObjType GetStageObjType() { return m_type; }
	/// <summary>
	/// ステージオブジェクト種類の設定
	/// </summary>
	/// <param name="type">ステージオブジェクト種類</param>
	void SetStageObjType(const StageObjType& type) { m_type = type; }

	/// <summary>
	/// モデルの取得
	/// </summary>
	/// <returns>モデルのポインタ</returns>
	DirectX::Model* GetModel() { return m_model.get(); }
	/// <summary>
	/// モデルの設定
	/// </summary>
	/// <param name="model">モデルのポインタ</param>
	void SetModel(std::unique_ptr<DirectX::Model> model) { m_model = std::move(model); }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const DirectX::SimpleMath::Matrix GetWorldMatrix() { return m_world; }
	/// <summary>
	/// ワールド行列の設定
	/// </summary>
	/// <param name="world">ワールド行列</param>
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns>当たり判定基底クラスのポインタ</returns>
	CollisionObject* GetCollisionObject() { return m_collision.get(); }
	/// <summary>
	/// 当たり判定の設定
	/// </summary>
	/// <param name="obj">当たり判定基底クラスのポインタ</param>
	void SetCollisionObject(std::unique_ptr<CollisionObject> obj) { m_collision = std::move(obj); }

	/// <summary>
	/// 共通デバッグ描画
	/// </summary>
	void CommonDebugRender()
	{
		using namespace DirectX;

		//	座標の取得
		SimpleMath::Vector3 pos = GetPos();
		ImGui::Text("Position");
		ImGui::InputFloat("P_X", &pos.x);
		ImGui::InputFloat("P_Y", &pos.y);
		ImGui::InputFloat("P_Z", &pos.z);

		//	回転の取得
		SimpleMath::Vector3 rot = GetRot();
		ImGui::Text("Rotation");
		if (ImGui::InputFloat("R_X", &rot.x))
		{
			//	回転クォータニオンの計算
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}
		else if (ImGui::InputFloat("R_Y", &rot.y))
		{
			//	回転クォータニオンの計算
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}
		else if (ImGui::InputFloat("R_Z", &rot.z))
		{
			//	回転クォータニオンの計算
			SimpleMath::Quaternion rotate = CalculationRot(rot);
			SetRotQua(rotate);
		}

		SimpleMath::Vector3 sca = GetSca();
		ImGui::Text("Scale");
		ImGui::InputFloat("S_X", &sca.x);
		ImGui::InputFloat("S_Y", &sca.y);
		ImGui::InputFloat("S_Z", &sca.z);

		SetPos(pos);
		SetRot(rot);
		SetSca(sca);
	}

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IStageObject() = default;

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
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	virtual void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugRender() = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// リセット
	/// </summary>
	virtual void Reset() = 0;

	/// <summary>
	/// アクティブ状態の取得
	/// </summary>
	/// <returns>アクティブ状態</returns>
	const bool& GetIsHitActive() { return m_isHitActive; }
	/// <summary>
	/// アクティブ状態の設定
	/// </summary>
	/// <param name="flag">アクティブ状態</param>
	void SetIsHitActive(const bool& flag) { m_isHitActive = flag; }

private:
	/// <summary>
	/// 回転の計算
	/// </summary>
	/// <param name="rot">回転ベクトル</param>
	/// <returns>回転クォータニオン</returns>
	const DirectX::SimpleMath::Quaternion& CalculationRot(const DirectX::SimpleMath::Vector3& rot)
	{
		using namespace DirectX;

		//	回転クォータ二オン
		SimpleMath::Quaternion rotate = SimpleMath::Quaternion::Identity;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;

		//	回転を掛ける
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(rot.z));
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(rot.x));
		q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(rot.y));
		
		//	回転の計算
		rotate = q * rotate;
		return rotate;
	}

private:
	//	種類
	StageObjType m_type;
	//	回転ベクトル
	DirectX::SimpleMath::Vector3 m_rotVec;

	//	当たり判定の有無
	bool m_isHitActive;

	//	モデル
	std::unique_ptr<DirectX::Model> m_model;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//	当たり判定
	std::unique_ptr<CollisionObject> m_collision;
};
#endif		// ISTAGE_OBJECT_DEFINED