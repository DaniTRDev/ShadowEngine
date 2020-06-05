#pragma once
#include "pch.h"

__declspec(align(16))
struct constant_buffer_decl {

	matrix m_world;
	matrix m_view;
	matrix m_project;
	unsigned int m_time;
};

class constant_buffer {

public:

	bool create_constant_buffer(ID3D11Device * dvc, void* buffer, UINT sizeof_buffer) {


		D3D11_BUFFER_DESC buff_desc = {};
		buff_desc.Usage = D3D11_USAGE_DEFAULT;
		buff_desc.ByteWidth = sizeof_buffer;
		buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buff_desc.CPUAccessFlags = 0;
		buff_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = buffer;

		dvc->CreateBuffer(&buff_desc, &init_data, &m_constant_buffer);

		if (m_constant_buffer == nullptr) { /*This one is unique, so it can be logged */

			LOG_ERROR("Cant create ID3D11Buffer_Constant_Buffer ptr!");
			return false;
		}
		LOG_INFO("Created ID3D11Buffer_Constant_Buffer ptr!");

		return true;
	}

	void update_constant_buffer_content(ID3D11DeviceContext * ctx, void* buff) { /*UPDATE m_time...*/
		ctx->UpdateSubresource(m_constant_buffer, NULL, NULL, buff, NULL, NULL);
	}

	void release() {
		m_constant_buffer->Release();
	}

	ID3D11Buffer* m_constant_buffer;
};