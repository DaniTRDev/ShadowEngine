#pragma once
#include "pch.h"

class idxgi_factory {

public:

	static std::shared_ptr<shadow_swapchain> get_swap() { static auto ptr = std::make_shared< shadow_swapchain>(); return ptr; }
	static std::shared_ptr<shadow_dvc_ctx> get_dvc_context() { static auto ptr = std::make_shared<shadow_dvc_ctx>(); return ptr; }
	static std::shared_ptr<vertex_shader> get_vertex_shader() { static auto ptr = std::make_shared<vertex_shader>(); return ptr; }
	static std::shared_ptr<pixel_shader> get_pixel_shader() { static auto ptr = std::make_shared<pixel_shader>(); return ptr; }
	static std::shared_ptr<constant_buffer> get_constant_buff() { static auto ptr = std::make_shared<constant_buffer>(); return ptr; }
	static std::shared_ptr<idxgi_factory> get() { static auto ptr = std::make_shared<idxgi_factory>(); return ptr; }

public:

	bool init(HWND hWnd) {

		CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

		if (factory == nullptr) {

			LOG_ERROR("Cant create IDXGIFactory ptr!");
			return false;
		}
		LOG_INFO("Created IDXGIFactory ptr!");

		if (!get_dvc_context()->init()) return false;
			LOG_INFO("Created Shadow_Device_Context ptr!");

		RECT rc;
		GetWindowRect(hWnd, &rc);

		if (!get()->get_swap()->init(factory, get_dvc_context()->m_device, hWnd, rc.right, rc.bottom )) return false;
		LOG_INFO("Created Shadow_Swapchain ptr!");

		if (!get()->get_vertex_shader()->init(get_dvc_context()->m_device)) return false;
		LOG_SHADER("Created Shadow_Vertex_Shader ptr!");

		if (!get()->get_pixel_shader()->init(get_dvc_context()->m_device)) return false;
		LOG_SHADER("Created Shadow_Pixel_Shader ptr!");

		constant_buffer_decl cc_buff;
		cc_buff.m_time = 0;

		if (!get()->get_constant_buff()->create_constant_buffer(get()->get_dvc_context()->m_device, &cc_buff, sizeof(constant_buffer_decl))) return false;
		LOG_INFO("Created Shadow_Constant_Buffer ptr!");

		return true;
	}

	void release() {

		factory->Release();
	}

	IDXGIFactory* factory;

};