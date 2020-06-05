#pragma once
#include "pch.h"

struct texture_info {

	std::uint32_t text_id;
	ID3D11Texture2D * m_texture;
	ID3D11ShaderResourceView * m_srv;

};

class texture_mgr {

public:

	static texture_info at(std::string_view texture_dict, std::string_view texture) {

		auto selected_dir = textures_array[JOAAT(texture_dict.data())];
		
		auto selected_texture = selected_dir[JOAAT(texture.data())];

		return selected_texture;
	}


	static void add_texture(std::string_view texture_dict, std::string_view texture_name, 
		ID3D11Texture2D * texture, ID3D11ShaderResourceView * srv) {

		texture_info text;

		text.m_srv == srv;
		text.m_texture = texture;

		auto cur_texture_dict = textures_array[JOAAT(texture_dict.data())];

		cur_texture_dict.insert({ JOAAT(texture_name.data()), text});

	}

private:

	static size_t texture_dict_count;

	static std::unordered_map<std::uint32_t, std::map<std::uint32_t, texture_info>> textures_array;

};