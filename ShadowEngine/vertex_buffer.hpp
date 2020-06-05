#pragma once
#include "pch.h"


struct vertex_buffer_decl {

	vector_3d position;
	float  color[4]; //RGBA

};

class vertex_buffer {

public:

	bool create_new_vertex(ID3D11Device * dvc, void * vertex_ptr, UINT a_list_size /*ARRAYSIZE(vertex_ptr)*/, UINT a_vertex_size, 
		void* shader_ptr, size_t shader_size) {

		D3D11_BUFFER_DESC buff_desc = {};
		buff_desc.Usage = D3D11_USAGE_DEFAULT;
		buff_desc.ByteWidth = a_list_size * a_vertex_size;
		buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buff_desc.CPUAccessFlags = 0;
		buff_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = vertex_ptr;

		vertex_size = a_vertex_size;
		list_size = a_list_size;

		dvc->CreateBuffer(&buff_desc, &init_data, &vertex_buffer_ptr);

		if (vertex_buffer_ptr == nullptr) {

			LOG_ERROR("Cant create ID3D11Buffer_Vertex_Buffer ptr!");
			LOG_ERROR("Vertex Struct Size: " + (const char*)vertex_size);
			LOG_ERROR("Vertex List Size: " + (const char*)list_size);
			return false;
		} //no need to log all this shit as it will be called 2bill times per frame


		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
			{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	     	{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		dvc->CreateInputLayout(layout, ARRAYSIZE(layout), shader_ptr, shader_size, &vertex_layout);

		if (vertex_layout == nullptr) {

			LOG_ERROR("Cant create Vertex_Buffer_Input_Layout");
			return false;
		}

		return true;
	}

	void release() {

		vertex_buffer_ptr->Release();
		vertex_layout->Release();
	}

	UINT vertex_size; //size of vertex struct
	UINT list_size; //ARRAYSIZE(vertex_ptr)

	ID3D11Buffer* vertex_buffer_ptr;
	ID3D11InputLayout* vertex_layout;
};