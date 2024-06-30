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
    //  ��ʃ��[�h��ݒ肷��֐�
    void SetFullscreenState(BOOL value);

    //  ��ʂ̒��S���W�̐ݒ�
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

    //  ��ʂ̒��S���W
    DirectX::SimpleMath::Vector2 m_center;

    BOOL m_fullscreen;

    // �L�[�{�[�h�X�e�[�g�g���b�J�[
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
    // �}�E�X�X�e�[�g�g���b�J�[
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;
    // ���ʃX�e�[�g�ւ̃|�C���^
    std::unique_ptr<DirectX::CommonStates> m_states;
    //  �V�[���}�l�[�W���[�̃|�C���^
    std::unique_ptr<SceneManager> m_sceneManager;
    // �V���h�E�}�b�v
    std::unique_ptr<ShadowMap> m_shadowMap;

    // �I�[�f�B�I�G���W���̃��j�[�N�|�C���^
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
};
