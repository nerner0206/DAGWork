//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "Scenes/TitleScene.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    ShowCursor(false);

    //	マウス
    Mouse::State mo = Mouse::Get().GetState();
    mo.positionMode = Mouse::MODE_ABSOLUTE;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());

    //  シーンマネージャの初期化
    m_sceneManager->Initialize();
    //  タイトルシーンをセット
    m_sceneManager->SetScene(new TitleScene());
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    //  キーボードステートトラッカーの更新
    m_keyboardTracker.Update(Keyboard::Get().GetState());
    //  マウスステートトラッカーの更新
    m_mouseTracker.Update(Mouse::Get().GetState());

    // オーディオエンジンの更新
    if (!m_audioEngine->Update())
    {
        // No audio device is active
        if (m_audioEngine->IsCriticalError())
        {
            OutputDebugString(L"AudioEngine Error!\n");
        }
    }

    //  シーンの更新
    m_sceneManager->Update(elapsedTime);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
    //  影の描画
    m_sceneManager->ShadowRender();

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");

    // TODO: Add your rendering code here.
    //  シーンの描画
    m_sceneManager->Render();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}
void Game::SetFullscreenState(BOOL value)
{
    m_fullscreen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}
//  画面の中心座標の設定
void Game::SetScreenCenter(const DirectX::SimpleMath::Vector2& center)
{
    //  ユーザーリソースを渡す
    UserResources* ur = UserResources::GetInstance();
    ur->SetCenterPos(center);
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    // 共通ステートオブジェクトの作成
    m_states = std::make_unique<CommonStates>(device);

    // シャドウマップ用のオブジェクトを作成
    m_shadowMap = std::make_unique<ShadowMap>();
    // カスケードの範囲テーブル
    float cascadeRangeTable[3] = { 10.0f, 30.0f, 50.0f };
    // シャドウマップ用のオブジェクトの初期化
    m_shadowMap->Initialize(device, cascadeRangeTable, 3, L"Resources/Shader/cso/Shadow");

    // オーディオエンジンの作成
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
    m_audioEngine = std::make_unique<AudioEngine>(eflags);

    //  ユーザーリソースを渡す
    UserResources* ur = UserResources::GetInstance();
    //  各リソースを設定する
    ur->SetStepTimerStates(&m_timer);
    ur->SetDeviceResources(m_deviceResources.get());
    ur->SetKeyboardStateTracker(&m_keyboardTracker);
    ur->SetMouseStateTracker(&m_mouseTracker);
    ur->SetCommonStates(m_states.get());
    ur->SetShadowMap(m_shadowMap.get());
    ur->SetAudioEngine(m_audioEngine.get());
    
    //  シーンマネージャーの作成
    if (!m_sceneManager) m_sceneManager = std::make_unique<SceneManager>();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
