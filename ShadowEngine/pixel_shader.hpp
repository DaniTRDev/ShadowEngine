#pragma once
#include "pch.h"

class pixel_shader {

public:

	bool init(ID3D11Device* dvc) {

		ID3DBlob* blob;
		ID3DBlob* error;

		D3DCompileFromFile(L"pixel_shader.hlsl", nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &blob, &error);

		if (error != nullptr) {

			LOG_ERROR("Error Compiling Pixel Shader!");
			LOG_ERROR((const char*)error->GetBufferPointer());
			error->Release();
			return false;
		}
		LOG_SHADER("Compiled Pixel Shader!");

		dvc->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_pixel_shader);

		if (m_pixel_shader == nullptr) {

			LOG_ERROR("Cant create ID3D11PixelShader ptr!");
			return false;
		}
		LOG_SHADER("Created ID3D11PixelShader ptr!");

		return true;
	}

	void release() {
		blob->Release();
		m_pixel_shader->Release();
	}

public:
	ID3DBlob* blob;
	ID3D11PixelShader* m_pixel_shader;
};