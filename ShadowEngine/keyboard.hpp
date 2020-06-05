#pragma once
#include "pch.h"

namespace keyboard_input {


	inline void on_key_down(unsigned int key) {

		/*LOCAL_PLAYER->COORDS*/
		auto l_player = local_player::get();

		if (key == 0x57) /*W*/
			l_player->player_cam_pos.x = 1;
		else if (key == 0x53) /*S*/
			l_player->player_cam_pos.x = -1;

		else if (key == 0x44) /*D*/
			l_player->player_cam_pos.y = 1;
		else if (key == 0x41) /*A*/
			l_player->player_cam_pos.y = -1;

	}

	inline void on_key_up(unsigned int wparam) {

		/*LOCAL_PLAYER->COORDS*/
		auto l_player = local_player::get();

		l_player->player_cam_pos.x = 0;
		l_player->player_cam_pos.y = 0;

	}

	inline bool handle_keyboard_input(UINT msg, WPARAM wparam, LPARAM lparam) {

		switch (msg)
		{

		case WM_KEYUP: {

			on_key_up((unsigned int)wparam);

			return true;

		} break;

		case WM_KEYDOWN: {

			on_key_down((unsigned int)wparam);

			return true;

		} break;

		}

		return false;
	}

};