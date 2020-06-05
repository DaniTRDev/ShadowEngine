#pragma once
#include "pch.h"

class local_player {

public:

	static local_player* get() { static auto ptr = local_player(); return &ptr; }

public:

	local_player() {
	
	
		player_cam_pos.x = 0;
		player_cam_pos.y = 0;
		player_cam_pos.z = -2;
	
	}

public:

	vector_3d player_cam_pos;
	vector_3d player_cam_rot;
	matrix world_cam;

};