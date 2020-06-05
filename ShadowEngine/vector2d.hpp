#pragma once
#include "pch.h"

class vector2d {

public:

	vector2d(float a_x, float a_y) : x(a_x), y(a_y) {}
	vector2d(float a_float) : x(a_float), y(a_float) {}

	vector2d() : x(0.0f), y(0.0f) {}

	float x, y;

};