#pragma once


class window {

public:

	bool create(const char* wnd_class, const char* wnd_name, vector2d a_size, void* wndproc) {

		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = NULL;
		wc.lpszClassName = wnd_class;
		wc.lpszMenuName = "";
		wc.style = NULL;
		wc.lpfnWndProc = (WNDPROC)wndproc;

		size = a_size;

		::RegisterClassEx(&wc);

		hWnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wnd_name, wnd_class,
			WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, a_size.x, a_size.y,
			NULL, NULL, NULL, this);

		if (hWnd == NULL) return false;

		is_running = true;

		::ShowWindow(hWnd,	SW_NORMAL);
		::UpdateWindow(hWnd);

		return true;
	}

	void destroy() {

		DestroyWindow(hWnd);

	}

protected:

	HWND hWnd;
	bool is_running;

	vector2d size;

	WNDCLASSEX wc;
};