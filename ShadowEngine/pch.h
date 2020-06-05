#pragma once

/*window APIs*/

/*D3D11 APIs*/
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <Windows.h>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <optional>
#include <vector>
#include <ostream>
#include <sstream>
#include <timeapi.h>

#pragma comment (lib, "winmm.lib")


#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

void log_text(std::string_view text, std::uint16_t color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	std::cout << text.data() << std::endl;
}

#define LOG_INFO(label) log_text("[INFO]" + (std::string)label, CYAN);
#define LOG_THREAD(label) log_text("[THREADING]" + (std::string)label, GREEN);
#define LOG_SHADER(label) log_text("[SHADERS]" + (std::string)label, BLUE);
#define LOG_ERROR(label) log_text("[ERROR]" + (std::string)label, RED);
#define LOG_CUSTOM_COLOR(label, col) log_text(label, col);

constexpr char ToLower(const char c)
{
	return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
std::uint32_t joaat(const char* str) {
	std::uint32_t hash = 0;
	while (*str)
	{
		hash += ToLower(*str++);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

#define JOAAT(label) joaat(label)

/*size things & coords*/
#include "vector2d.hpp"
#include "vector3d.hpp"
#include "vector4d.hpp"
#include "matrix.hpp"

/* D3D11 Stuff*/
#include "device_context.hpp"
#include "swapchain.hpp"
#include "constant_buffer.hpp"
#include "pixel_shader.hpp"
#include "vertex_shader.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "idxgi_factory.hpp"

/*ENTITIES*/
#include "local_player.hpp"

/*RENDERER*/
#include "renderer.hpp"

/*inputs*/
#include "mouse.hpp"
#include "keyboard.hpp"

/*window mgr*/
#include "window_base.hpp"
#include "main_game_window.hpp"
