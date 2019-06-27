//
// Game.h
//

#pragma once

#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game() noexcept;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_world2;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;
	std::unique_ptr<DirectX::Model> m_model_skull;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	float m_pitch;
	float m_yaw;
	DirectX::SimpleMath::Vector3 m_cameraPos;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	enum PSConstantBuffer
	{
		PS_LIGHT,
		PSNumConstantBuffers
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> ps_d3dConstantBuffers[PSNumConstantBuffers];

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	


    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};
