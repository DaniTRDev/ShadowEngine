// ShadowEngine.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include "pch.h"

int main()
{
   
	auto main_wnd_ptr = main_game_window::get();

	bool wnd_state = main_wnd_ptr->create("Shadow Engine", "Shadow Engine", { 1024, 700 }, (void*)&main_window_wndproc);
	
	if (!wnd_state) { LOG_ERROR("Cant create main_game window!"); return 0; }

	LOG_INFO("Main window created!");

	if (!idxgi_factory::get()->init(main_wnd_ptr->get_hwnd())) { LOG_ERROR("Cant create Shadow_Idxgi_Factory ptr!"); return 0; }
	LOG_INFO("Created Shadow_Idxgi_Factory ptr!");

	renderer::get()->init();
	LOG_INFO("Initialized Renderer!");

	while (main_wnd_ptr->get_if_is_running()) {

		main_wnd_ptr->update_main_window();

		renderer::get()->update_constant_buffer(main_wnd_ptr->get_size());
		renderer::get()->render(main_wnd_ptr->get_size());

	}

	main_wnd_ptr->release();



	return 0;
}

