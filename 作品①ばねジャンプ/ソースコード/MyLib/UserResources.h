//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// 様々な場所で使用するユーザーリソースクラスのヘッダーファイル（シングルトン化）
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef USER_RESOURCES_DEFINED
#define USER_RESOURCES_DEFINED

#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"

#include "Common/ShadowMap.h"

#include <Keyboard.h>
#include <Mouse.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Effects.h>
#include <Audio.h>

/// <summary>
/// ユーザーリソースクラス
/// </summary>
class UserResources
{
public:
	//	ウィンドウの幅
	static const int WINDOW_WIDTH = 1280;
	//	ウィンドウの高さ
	static const int WINDOW_HEIGHT = 720;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UserResources();
	/// <summary>
	///	デストラクタ
	/// </summary>
	~UserResources();

	/// <summary>
	/// ユーザーリソースクラスのインスタンスの取得
	/// </summary>
	/// <returns>ユーザーリソースクラスのポインタ</returns>
	static UserResources* GetInstance()
	{
		//	ポインタが作られていない場合、新しくポインタを作成する
		if (s_userResources.get() == nullptr) 
			s_userResources.reset(new UserResources());

		return s_userResources.get();
	}

	/// <summary>
	/// ステップタイマークラスの設定
	/// </summary>
	/// <param name="timer">ステップタイマークラスのポインタ</param>
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }
	/// <summary>
	/// ステップタイマークラスの取得
	/// </summary>
	/// <returns>ステップタイマークラスのポインタ</returns>
	DX::StepTimer* GetStepTimer() { return m_timer; }

	/// <summary>
	/// デバイスリソースクラスの設定
	/// </summary>
	/// <param name="deviceResources">デバイスリソースクラスのポインタ</param>
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }
	/// <summary>
	/// デバイスリソースクラスの取得
	/// </summary>
	/// <returns>デバイスリソースクラスのポインタ</returns>
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }

	/// <summary>
	/// キーボードステートトラッカークラスの設定
	/// </summary>
	/// <param name="tracker">キーボードステートトラッカークラスのポインタ</param>
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_keyboardTracker = tracker; }
	/// <summary>
	/// キーボードステートトラッカークラスの取得
	/// </summary>
	/// <returns>キーボードステートトラッカークラスのポインタ</returns>
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardTracker; }

	/// <summary>
	/// マウスステートトラッカークラスの設定
	/// </summary>
	/// <param name="tracker">マウスステートトラッカークラスのポインタ</param>
	void SetMouseStateTracker(DirectX::Mouse::ButtonStateTracker* tracker) { m_mouseTracker = tracker; }
	/// <summary>
	/// マウスステートトラッカークラスの取得
	/// </summary>
	/// <returns>マウスステートトラッカークラスのポインタ</returns>
	DirectX::Mouse::ButtonStateTracker* GetMouseStateTracker() { return m_mouseTracker; }

	/// <summary>
	/// 共通ステートクラスの設定
	/// </summary>
	/// <param name="states">共通ステートクラスのポインタ</param>
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }
	/// <summary>
	/// 共通ステートクラスの取得
	/// </summary>
	/// <returns>共通ステートクラスのポインタ</returns>
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	/// <summary>
	/// オーディオエンジンの設定
	/// </summary>
	/// <param name="audioEngine">オーディオエンジンのポインタ</param>
	void SetAudioEngine(DirectX::AudioEngine* audioEngine) { m_audioEngine = audioEngine; }
	/// <summary>
	/// オーディオエンジンの取得
	/// </summary>
	/// <returns>オーディオエンジンのポインタ</returns>
	DirectX::AudioEngine* GetAudioEngine() { return m_audioEngine; }

	/// <summary>
	/// シャドウマップクラスの設定
	/// </summary>
	/// <param name="shadowMap">シャドウマップクラスのポインタ</param>
	void SetShadowMap(ShadowMap* shadowMap) { m_shadowMap = shadowMap; }
	/// <summary>
	/// シャドウマップクラスの取得
	/// </summary>
	/// <returns>シャドウマップクラスのポインタ</returns>
	ShadowMap* GetShadowMap() { return m_shadowMap; }

	/// <summary>
	/// 中心座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetCenterPos(const DirectX::SimpleMath::Vector2& pos) { m_centerPos = pos; }

	/// <summary>
	/// 中心座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	const DirectX::SimpleMath::Vector2 GetCenterPos() { return m_centerPos; }

	/// <summary>
	/// ラープ関数
	/// </summary>
	/// <param name="start">開始値</param>
	/// <param name="end">終了値</param>
	/// <param name="t">時間</param>
	/// <returns>補間値</returns>
	float Lerp(float start, float end, float t) { return (1 - t) * start + t * end; }

private:
	//	ユーザーリソースクラスのポインタ
	static std::unique_ptr<UserResources> s_userResources;

	// ステップタイマークラスのポインタ
	DX::StepTimer* m_timer;
	// デバイスリソースクラスのポインタ
	DX::DeviceResources* m_deviceResources;
	// キーボードステートトラッカークラスのポインタ
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;
	// マウスステートトラッカークラスのポインタ
	DirectX::Mouse::ButtonStateTracker* m_mouseTracker;
	// 共通ステートクラスのポインタ
	DirectX::CommonStates* m_states;
	//	シャドウマップクラスのポインタ
	ShadowMap* m_shadowMap;
	//	オーディオエンジンのポインタ
	DirectX::AudioEngine* m_audioEngine;

	//	画面の中心座標
	DirectX::SimpleMath::Vector2 m_centerPos;
};
#endif // !USER_RESOURCES_DEFINED