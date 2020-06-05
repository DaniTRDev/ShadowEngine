#pragma once
#include "pch.h"

class vertex_shader {

public:

	bool init(ID3D11Device* dvc) {

		ID3DBlob* error;

		D3DCompileFromFile(L"vertex_shader.hlsl", nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &blob, &error);

		if (error != nullptr) {

			LOG_ERROR("Error Compiling Vertex Shader!");
			LOG_ERROR((const char*)error->GetBufferPointer());
			error->Release();
			return false;
		}
		LOG_SHADER("Compiled Vertex Shader!");

		dvc->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_vertex_shader);

		if (m_vertex_shader == nullptr) {

			LOG_ERROR("Cant create ID3D11VertexShader ptr!");
			return false;
		}
		LOG_SHADER("Created ID3D11VertexShader ptr!");

		return true;
	}

	void release() {
		blob->Release();
		m_vertex_shader->Release();
	}


public:

	ID3DBlob* blob;
	ID3D11VertexShader* m_vertex_shader;
};