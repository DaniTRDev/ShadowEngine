#pragma once
#include "pch.h"

namespace mouse_input {


	enum mouse_event_enum : int {

		LClickPress,
		LClickRelease,
		RClickPress,
		RClickRelease,
		WheelClickPress,
		WheelClickRelease,
		WheelForward,
		WheelBackward,
		NONE
	};
	inline mouse_event_enum mouse_event;

	inline int mouse_wheel_distance = 0; //gets the distance the mouse wheel has been desplaced

	struct mouse_pos_decl { int x, y; };
	inline mouse_pos_decl mouse_pos;

	inline bool handle_mouse_key(UINT msg, WPARAM wparam, LPARAM lparam) {

		mouse_event = mouse_event_enum::NONE; //if no of this events is reached no mouse event // same as resetting it every tick

		switch (msg)
		{

		case WM_LBUTTONDOWN: {
			mouse_event = mouse_event_enum::LClickPress;
			return true;
		} break;
		case WM_LBUTTONUP: {
			mouse_event = mouse_event_enum::LClickRelease;
			return true;
		} break;

		case WM_RBUTTONDOWN: {
			mouse_event = mouse_event_enum::RClickPress;
			return true;
		} break;
		case WM_RBUTTONUP: {
			mouse_event = mouse_event_enum::RClickRelease;
			return true;
		} break;

		case WM_MBUTTONDOWN: {
			mouse_event = mouse_event_enum::WheelClickPress;
			return true;
		} break;
		case WM_MBUTTONUP: {
			mouse_event = mouse_event_enum::WheelClickRelease;
			return true;
		} break;

		case WM_MOUSEWHEEL: {

			auto wheel_pos = HIWORD(lparam);

			if (wheel_pos < 0) 	mouse_event = mouse_event_enum::WheelBackward;
			else mouse_event_enum::WheelForward;

			mouse_wheel_distance = wheel_pos;

			return true;
		} break;


			return false;
		}

	}
};