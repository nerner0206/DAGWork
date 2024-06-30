//--------------------------------------------------------------------------------------
// File: IScene.h
//
// シーン基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef ISCENE_DEFINED
#define ISCENE_DEFINED

#include"SceneManager.h"

#include "GameObjects/Common/SkyDome.h"

#include "MyLib/UserResources.h"
#include "MyLib/AudioResources.h"
#include "MyLib/UserInterface.h"

/// <summary>
/// シーン基底クラス
/// </summary>
class IScene
{
public:
	//	シーンの種類
	enum class SceneKind
	{
		TitleScene,
		SelectScene,
		PlayScene
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	IScene(const SceneKind& kind) : 
		m_sceneManager(nullptr),
		m_lightRange(0.0f),
		m_kind(kind)
	{
		//	ユーザーリソースの取得
		m_ur = UserResources::GetInstance();
		//	音リソースの取得
		m_ar = AudioResources::GetInstance();

		//	スカイドームの作成
		m_skyDome = std::make_unique<SkyDome>();
	}

	/// <summary>
	/// シーン管理クラスの設定
	/// </summary>
	/// <param name="sceneManager">シーン管理クラスのポインタ</param>
	void SetSceneManager(SceneManager* sceneManager) { m_sceneManager = sceneManager; }
	/// <summary>
	/// シーン管理クラスの取得
	/// </summary>
	/// <returns>シーン管理クラスのポインタ</returns>
	SceneManager* GetSceneManager() { return m_sceneManager; }

	/// <summary>
	/// ユーザーリソースクラスの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	UserResources* GetUserResources() { return m_ur; }

	/// <summary>
	/// 音リソースクラスの取得
	/// </summary>
	/// <returns>音リソースクラスのポインタ</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// スカイドームクラスの設定
	/// </summary>
	/// <param name="skyDome">スカイドームクラスのユニークポインタ</param>
	void SetSkyDome(std::unique_ptr<SkyDome> skyDome) { m_skyDome = std::move(skyDome); }
	/// <summary>
	/// スカイドームクラスの取得
	/// </summary>
	/// <returns>スカイドームクラスのポインタ</returns>
	SkyDome* GetSkyDome() { return m_skyDome.get(); }

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	const DirectX::SimpleMath::Matrix GetViewMatrix() { return m_view; }
	/// <summary>
	/// ビュー行列の設定
	/// </summary>
	/// <param name="view">ビュー行列</param>
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	/// <summary>
	/// 射影行列の取得
	/// </summary>
	/// <returns>射影行列</returns>
	const DirectX::SimpleMath::Matrix GetProjMatrix() { return m_proj; }
	/// <summary>
	/// 射影行列の設定
	/// </summary>
	/// <param name="proj">射影行列</param>
	void SetProjMatrix(const DirectX::SimpleMath::Matrix& proj) { m_proj = proj; }

	/// <summary>
	/// ライトの座標の取得
	/// </summary>
	/// <returns>ライト座標</returns>
	const DirectX::SimpleMath::Vector3 GetLightPos() { return m_lightPos; }
	/// <summary>
	/// ライトの座標の設定
	/// </summary>
	/// <param name="lightPos">ライト座標</param>
	void SetLightPos(const DirectX::SimpleMath::Vector3& lightPos) { m_lightPos = lightPos; }
	/// <summary>
	/// ライトの目標座標の取得
	/// </summary>
	/// <returns>ライト目標座標</returns>
	const DirectX::SimpleMath::Vector3 GetLightTarget() { return m_lightTarget; }
	/// <summary>
	/// ライトの目標座標の設定
	/// </summary>
	/// <param name="lightTarget">ライト目標座標</param>
	void SetLightTarget(const DirectX::SimpleMath::Vector3& lightTarget) { m_lightTarget = lightTarget; }
	/// <summary>
	/// ライトの影響範囲の取得
	/// </summary>
	/// <returns>ライトの影響範囲</returns>
	const float GetLightRange() { return m_lightRange; }
	/// <summary>
	/// ライトの影響範囲の設定
	/// </summary>
	/// <param name="lightRange">ライトの影響範囲</param>
	void SetLightRange(const float& lightRange) { m_lightRange = lightRange; }

	/// <summary>
	/// カメラの座標を取得
	/// </summary>
	/// <returns>カメラの座標</returns>
	const DirectX::SimpleMath::Vector3 GetCameraPos() { return m_cameraPos; }
	/// <summary>
	/// カメラの座標を設定
	/// </summary>
	/// <param name="cameraPos">カメラの座標</param>
	void SetCameraPos(const DirectX::SimpleMath::Vector3& cameraPos) { m_cameraPos = cameraPos; }
	/// <summary>
	/// カメラの目標座標を取得
	/// </summary>
	/// <returns>カメラの目標座標</returns>
	const DirectX::SimpleMath::Vector3 GetCameraTarget() { return m_cameraTarget; }
	/// <summary>
	/// カメラの目標座標を設定
	/// </summary>
	/// <param name="cameraTarget">カメラの目標座標</param>
	void SetCameraTarget(const DirectX::SimpleMath::Vector3& cameraTarget) { m_cameraTarget = cameraTarget; }

	//	シーンの種類の取得
	const SceneKind GetSceneKind() { return m_kind; }

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IScene() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	virtual void Initialize(const int& mouseNumber) = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	virtual void Update(const float& elapsedTime) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Render() = 0;
	/// <summary>
	/// 影描画
	/// </summary>
	virtual void ShadowRender() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;

private:
	// シーン管理クラスのポインタ
	SceneManager* m_sceneManager;

	//	ユーザーリソースクラスのポインタ
	UserResources* m_ur;
	//	音リソースクラスのポインタ
	AudioResources* m_ar;

	//	シーンの種類
	SceneKind m_kind;

	//	スカイドームのユニークポインタ
	std::unique_ptr<SkyDome> m_skyDome;

	//	ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//	射影行列
	DirectX::SimpleMath::Matrix m_proj;

	// ライトの座標
	DirectX::SimpleMath::Vector3 m_lightPos;
	// ライトの目標座標
	DirectX::SimpleMath::Vector3 m_lightTarget;
	// ライトの影響範囲
	float m_lightRange;

	//	カメラの座標
	DirectX::SimpleMath::Vector3 m_cameraPos;
	//	カメラの目標座標
	DirectX::SimpleMath::Vector3 m_cameraTarget;
};
#endif // !ISCENE_DEFINED