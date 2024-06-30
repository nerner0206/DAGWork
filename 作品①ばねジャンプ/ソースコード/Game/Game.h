//
// Game.h
//

#pragma once

#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
#include "MyLib/SceneManager.h"
#include "Common/ShadowMap.h"
#include "MyLib/UserResources.h"

#include "imgui.h"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

public:
    //  画面モードを設定する関数
    void SetFullscreenState(BOOL value);

    //  画面の中心座標の設定
    void SetScreenCenter(const DirectX::SimpleMath::Vector2& center);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    //  画面の中心座標
    DirectX::SimpleMath::Vector2 m_center;

    BOOL m_fullscreen;

    // キーボードステートトラッカー
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
    // マウスステートトラッカー
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;
    // 共通ステートへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_states;
    //  シーンマネージャーのポインタ
    std::unique_ptr<SceneManager> m_sceneManager;
    // シャドウマップ
    std::unique_ptr<ShadowMap> m_shadowMap;

    // オーディオエンジンのユニークポインタ
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
};
