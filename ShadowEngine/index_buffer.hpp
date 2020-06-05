#pragma once
#include "pch.h"

class index_buffer {

public:


	bool create_new_index_buffer(ID3D11Device * dvc, void* buffer, UINT a_list_size) {

		D3D11_BUFFER_DESC buff_desc = {};
		buff_desc.Usage = D3D11_USAGE_DEFAULT;
		buff_desc.ByteWidth = 4 * a_list_size; //4 as it is the size of a single int
		buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buff_desc.CPUAccessFlags = 0;
		buff_desc.MiscFlags = 0;

		list_size = a_list_size;

		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = buffer;

		dvc->CreateBuffer(&buff_desc, &init_data, &m_index_buffer);

		if (m_index_buffer == nullptr) {

			LOG_ERROR("Cant create ID3D11Buffer_Index_Buffer");
			return false;
		}

		return true;
	}

	void release() {
		m_index_buffer->Release();
	}

public:

	ID3D11Buffer* m_index_buffer;
	UINT list_size;

};