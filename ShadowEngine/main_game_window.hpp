#pragma once
#include "pch.h"

class main_game_window : public window {

public:

	static main_game_window* get() { static auto ptr = main_game_window(); return &ptr; }

public:

	bool get_if_is_running() { return is_running; }
	void set_if_is_running(bool state) { is_running = state; }

	void update_main_window() {

		MSG msg;

		while ((::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(1);
	}

	void release() {

		idxgi_factory::get()->get_dvc_context()->release();
		idxgi_factory::get()->get_dvc_context().reset();
		
		renderer::get()->release();
		renderer::get().reset();

		idxgi_factory::get()->get_swap()->release();
		idxgi_factory::get()->get_swap().reset();

		idxgi_factory::get()->get_pixel_shader()->release();
		idxgi_factory::get()->get_pixel_shader().reset();

		idxgi_factory::get()->get_vertex_shader()->release();
		idxgi_factory::get()->get_vertex_shader().reset();

		idxgi_factory::get()->get_constant_buff()->release();
		idxgi_factory::get()->get_constant_buff().reset();

		idxgi_factory::get()->release();
		idxgi_factory::get().reset();

		destroy();

		this;
	}

	vector2d get_size() { return size; }

public:

	HWND get_hwnd() { return hWnd; }
};

LRESULT main_window_wndproc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) {


	if (keyboard_input::handle_keyboard_input(msg, wparam, lparam)) return ::DefWindowProc(hWnd, msg, wparam, lparam);

	if (mouse_input::handle_mouse_key(msg, wparam, lparam)) return ::DefWindowProc(hWnd, msg, wparam, lparam);

	if (msg == WM_DESTROY)
		main_game_window::get()->set_if_is_running(false);

	return ::DefWindowProc(hWnd, msg, wparam, lparam);

}