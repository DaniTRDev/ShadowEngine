#pragma once
#include "pch.h"

class vector_4d {

public:

	vector_4d() : x(0.f), y(0.f), z(0.f) {}
	vector_4d(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {}

	static vector_4d lerp(const vector_4d& start, const vector_4d& end, float delta)
	{
		vector_4d v;
		v.x = start.x*(1.0f - delta) + end.x*(delta);
		v.y = start.y*(1.0f - delta) + end.y*(delta);
		v.z = start.z*(1.0f - delta) + end.z*(delta);
		v.w = start.w*(1.0f - delta) + end.w*(delta);
		return v;
	}
	void cross(vector_4d &v1, vector_4d &v2, vector_4d &v3)
	{
		x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z *v3.y);
		y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x *v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x *v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	float x{}, y{}, z{}, w{};

	inline bool operator== (vector_4d b) {
		return x == b.x && y == b.y && z == b.z && w == b.w;
	}
	inline bool operator!= (vector_4d b) {
		return x != b.x && y != b.y && z != b.z && w != b.w;
	}

	inline bool operator> (vector_4d b) {
		return x > b.x && y > b.y && z > b.z && w > b.w;
	}
	inline bool operator< (vector_4d b) {
		return x < b.x && y < b.y && z < b.z && w < b.w;
	}

	inline void operator= (float b) {
		x = b;
		y = b;
		z = b;
		w = b;
	}
	inline void operator= (vector_4d b) {
		x = b.x;
		y = b.y;
		z = b.z;
		w = b.w;
	}

	inline void operator* (vector_4d b) {
		x = x * b.x;
		y = y * b.y;
		z = z * b.z;
		w = w * b.w;
	}
	inline void operator* (float b) {
		x = x * b;
		y = y * b;
		z = z * b;
		w = w * b;
	}

	inline void operator+ (vector_4d b) {
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
	}
	inline void operator+ (float b) {
		x += b;
		y += b;
		z += b;
		w += b;
	}

	inline void operator- (vector_4d b) {
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
	}
	inline void operator- (float b) {
		x -= b;
		y -= b;
		z -= b;
		w -= b;
	}
};