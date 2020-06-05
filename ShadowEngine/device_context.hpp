#pragma once
#include "pch.h"

class shadow_dvc_ctx {

public:

	bool init() {

		D3D_FEATURE_LEVEL feature_level[1] = { D3D_FEATURE_LEVEL_11_0 };


		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_level, 1,
			D3D11_SDK_VERSION, &m_device, nullptr, &m_context);

		if (m_device == nullptr || m_context == nullptr) {

			LOG_ERROR("Cant create ID3D11Device/ID3D11DeviceContext ptr!");
			return false;
		}
		LOG_INFO("Created ID3D11Device & ID3D11DeviceContext ptr!");



		return true;
	}

	void clear_render_color(ID3D11RenderTargetView* rtv, float red, float green, float blue, float alpha)
	{
		FLOAT clear_color[] = { red, green, blue, alpha };
		m_context->ClearRenderTargetView(rtv, clear_color);
		m_context->OMSetRenderTargets(1, &rtv, NULL);
	}

	void set_pixel_shader(ID3D11PixelShader * shader) {

		m_context->PSSetShader(shader, nullptr, NULL);
	}
	void set_vertex_shader(ID3D11VertexShader * shader) {

		m_context->VSSetShader(shader, nullptr, NULL);
	}

	void set_vertex_buffer(ID3D11Buffer* buff, ID3D11InputLayout* layout, UINT vertex_struct_size) {
		UINT offset = 0;

		m_context->IASetVertexBuffers(0, 1, &buff, &vertex_struct_size, &offset);
		m_context->IASetInputLayout(layout);

	}
	void set_index_buffer(ID3D11Buffer* buff, UINT list_size) {
		m_context->IASetIndexBuffer(buff, DXGI_FORMAT_R32_UINT, 0);
	}

	void set_view_port_size(UINT w, UINT h) {
		D3D11_VIEWPORT vp = {};
		vp.Width = (FLOAT)w;
		vp.Height = (FLOAT)h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		m_context->RSSetViewports(1, &vp);
	}

	void draw(UINT vertex_list_size) {

		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_context->Draw(vertex_list_size, 0);
	}
	void draw_indexed(UINT index_count, UINT start_vertex_index, UINT start_index_location) {
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
	}
	void draw_and_reutilice_vertices(UINT vertex_list_size) {

		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_context->Draw(vertex_list_size, 0);
	}

	void release() {

		m_device->Release();
		m_context->Release();
	}

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

};