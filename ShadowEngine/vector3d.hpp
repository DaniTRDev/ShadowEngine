#pragma once
#include "pch.h"

class vector_3d {

public:

	vector_3d() : x(0.f), y(0.f), z(0.f) {}
	vector_3d(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) {}

	static vector_3d lerp(const vector_3d& start, const vector_3d& end, float delta)
	{
		vector_3d v;
		v.x = start.x*(1.0f - delta) + end.x*(delta);
		v.y = start.y*(1.0f - delta) + end.y*(delta);
		v.z = start.z*(1.0f - delta) + end.z*(delta);
		return v;
	}

	float x{}, y{}, z{};
	inline bool operator== (vector_3d b) {
		return x == b.x && y == b.y && z == b.z;
	}
	inline bool operator!= (vector_3d b) {
		return x != b.x && y != b.y && z != b.z;
	}

	inline bool operator> (vector_3d b) {
		return x > b.x && y > b.y && z > b.z;
	}
	inline bool operator< (vector_3d b) {
		return x < b.x && y < b.y && z < b.z;
	}

	inline void operator= (float b) {
		x = b;
		y = b;
		z = b;
	}
	inline void operator= (vector_3d b) {
		x = b.x;
		y = b.y;
		z = b.z;
	}

	inline void operator* (vector_3d b) {
		x = x * b.x;
		y = y * b.y;
		z = z * b.z;
	}
	inline vector_3d operator* (float b) {
		vector_3d r;
		r.x = x * b;
		r.y = y * b;
		r.z = z * b;
		return r;
	}

	inline vector_3d operator+ (vector_3d b) {
		vector_3d r;
		r.x = x + b.x;
		r.y = y + b.y;
		r.z = z + b.z;
		return r;
	}
	inline void operator+ (float b) {
		x += b;
		y += b;
		z += b;
	}

	inline void operator- (vector_3d b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
	}
	inline void operator- (float b) {
		x -= b;
		y -= b;
		z -= b;
	}
};