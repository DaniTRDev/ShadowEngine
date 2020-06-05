#pragma once
#include "pch.h"


class shadow_swapchain {

public:

	bool init(IDXGIFactory* ptr, ID3D11Device * device, HWND hWnd, int w, int h) {

		DXGI_SWAP_CHAIN_DESC swap_desc;
		ZeroMemory(&swap_desc, sizeof(swap_desc));

		swap_desc.BufferCount = 1;
		swap_desc.BufferDesc.Width = w;
		swap_desc.BufferDesc.Height = h;
		swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_desc.BufferDesc.RefreshRate.Numerator = 60;
		swap_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_desc.OutputWindow = hWnd;
		swap_desc.SampleDesc.Count = 1;
		swap_desc.SampleDesc.Quality = 0;
		swap_desc.Windowed = TRUE;

		ptr->CreateSwapChain(device, &swap_desc, &m_swap_chain);

		if (m_swap_chain == nullptr) {

			LOG_ERROR("Cant create IDXGISwapChain ptr!");
			return false;
		}
		LOG_INFO("Created IDXGISwapChain ptr!");

		return create_rtv(device);
	}

	bool create_rtv(ID3D11Device * ptr) {

		m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_2d_buff);
		//m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture3D), (void**)&m_3d_buff);

		if (m_2d_buff == nullptr) {
			LOG_ERROR("Cant retrieve ID3D11Texture2D ptr!");
			return false;
		}

		ptr->CreateRenderTargetView(m_2d_buff, nullptr, &m_rtv);
		//device_context::get()->get_device()->CreateRenderTargetView(m_3d_buff, nullptr, &m_render_target_view);

		if (m_rtv == nullptr) {
			LOG_ERROR("Cant create ID3D11RenderTargetView ptr!");
			return false;
		}
		LOG_INFO("Created ID3D11RenderTargetView ptr!");

		return true;

	}

	void present() { m_swap_chain->Present(1, 0); }

	void release() {

		m_swap_chain->Release();
		m_2d_buff->Release();
		m_rtv->Release();

	}

public:

	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	ID3D11Texture2D* m_2d_buff;
	

};