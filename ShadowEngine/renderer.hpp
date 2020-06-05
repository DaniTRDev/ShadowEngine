#pragma once

class renderer {
	

public:

	static std::shared_ptr<renderer> get() { static auto ptr = std::make_shared<renderer>(); return ptr; }

public:

	void init() {

		world_cam.update_matrix_with_vec3(vector_3d(0, 0, -2));

		vertex_buffer_decl vertex[] = {


		{ vector_3d(-0.5f,-0.5f,-0.5f),    { 1.f, 0.f, 0.0f, 0.5f  } },
		{ vector_3d(-0.5f,0.5f,-0.5f),     { 1.f, 1.f, 0.0f, 0.5f  } },
		{ vector_3d(0.5f,0.5f,-0.5f),      { 1.f, 1.f, 0.0f, 0.5f  } },
		{ vector_3d(0.5f,-0.5f,-0.5f),     { 1.f, 0.f, 0.0f, 0.5f  } },

		//BACK FACE
		{ vector_3d(0.5f,-0.5f,0.5f),      { 0.f, 1.f, 0.f, 0.5f   } },
		{ vector_3d(0.5f,0.5f,0.5f),       { 0.f, 1.f, 1.f, 0.5f   } },
		{ vector_3d(-0.5f,0.5f,0.5f),      { 0.f, 1.f, 1.f, 0.5f   } },
		{ vector_3d(-0.5f,-0.5f,0.5f),     { 0.f, 1.f, 0.f, 0.5f   } }

		};

		buff = new vertex_buffer();
		buff->create_new_vertex(idxgi_factory::get_dvc_context()->m_device, vertex, ARRAYSIZE(vertex),
		sizeof(vertex_buffer_decl), idxgi_factory::get_vertex_shader()->blob->GetBufferPointer(), idxgi_factory::get_vertex_shader()->blob->GetBufferSize());

		unsigned int index_list[] =
		{
			//FRONT SIDE
			0,1,2,  //FIRST TRIANGLE
			2,3,0,  //SECOND TRIANGLE
			//BACK SIDE
			4,5,6,
			6,7,4,
			//TOP SIDE
			1,6,5,
			5,2,1,
			//BOTTOM SIDE
			7,0,3,
			3,4,7,
			//RIGHT SIDE
			3,2,5,
			5,4,3,
			//LEFT SIDE
			7,6,1,
			1,0,7
		};

		id_buff = new index_buffer();
		id_buff->create_new_index_buffer(idxgi_factory::get_dvc_context()->m_device, index_list, ARRAYSIZE(index_list));

	}

	void update_constant_buffer(vector2d size) {

		constant_buffer_decl cc;
		cc.m_time = ::GetTickCount();

		delta_pos += delta_time / 10.f;

		if (delta_pos > 1.0f)
			delta_pos = 0;

		delta_scale += delta_time / 0.55f;

		cc.m_world.clear();

		matrix temp;

		auto l_local_player = local_player::get();
		world_cam.clear();

		temp.clear();
		temp.set_x_rot(l_local_player->player_cam_rot.x);
		world_cam *= temp;

		temp.clear();
		temp.set_y_rot(l_local_player->player_cam_rot.y);
		world_cam *= temp;

		vector_3d new_pos = l_local_player->world_cam.get_vect3_trans() + world_cam.get_z_dir() * (l_local_player->player_cam_pos.x * 0.3f);

		new_pos = new_pos + world_cam.get_x_dir() * (l_local_player->player_cam_pos.y * 0.3f);

		world_cam.update_matrix_with_vec3(new_pos);

		l_local_player->world_cam = world_cam;

		//world_cam.update_matrix_with_vec3(vector_3d(0, 0, -2));
		world_cam.inverse();

		cc.m_view = world_cam;
		cc.m_project.set_perspective_fov_lh(1.57f, ((float)size.x / (float)size.y), 0.1f, 100.0f);

		/*update locally*/
		idxgi_factory::get_constant_buff()->update_constant_buffer_content(idxgi_factory::get_dvc_context()->m_context, &cc);

		/*ASYNC WITH SHADERS*/
		idxgi_factory::get_dvc_context()->m_context->PSSetConstantBuffers(0, 1, &idxgi_factory::get_constant_buff()->m_constant_buffer);
		idxgi_factory::get_dvc_context()->m_context->VSSetConstantBuffers(0, 1, &idxgi_factory::get_constant_buff()->m_constant_buffer);

	
		old_delta_time = new_delta_time;
		new_delta_time = ::GetTickCount();

		delta_time = (old_delta_time) ? ((new_delta_time - old_delta_time) / 1000.0f) : 0;
	}
	void check_mouse(vector2d size) {
		auto l_player = local_player::get();

		POINT current_mouse_pos = {};
		::GetCursorPos(&current_mouse_pos);

		l_player->player_cam_rot.x += (current_mouse_pos.y - (size.y / 2.0f)) * delta_time * 0.1f;
		l_player->player_cam_rot.y += (current_mouse_pos.x - (size.x / 2.0f)) * delta_time * 0.1f;

		::SetCursorPos((int)(size.x / 2.0f), (int)(size.y / 2.0f));
	}
	void render(vector2d size) {

		check_mouse(size);

		auto p_shadow_dvc_ctx = idxgi_factory::get_dvc_context();
		auto shadow_swap_chain = idxgi_factory::get_swap();

		p_shadow_dvc_ctx->clear_render_color(shadow_swap_chain->m_rtv, 0, 0.3f, 0.4f, 1);

		p_shadow_dvc_ctx->set_view_port_size(size.x, size.y);

		p_shadow_dvc_ctx->set_vertex_shader(idxgi_factory::get_vertex_shader()->m_vertex_shader); 
		p_shadow_dvc_ctx->set_pixel_shader(idxgi_factory::get_pixel_shader()->m_pixel_shader);
		/* UPDATE SHADERS -> IN REAL TIME SHADER EDITING*/

		/*SET A VERTEX TO DRAW -> TESTING*/
		p_shadow_dvc_ctx->set_vertex_buffer(buff->vertex_buffer_ptr, buff->vertex_layout, buff->vertex_size);
		p_shadow_dvc_ctx->set_index_buffer(id_buff->m_index_buffer, id_buff->list_size);

		p_shadow_dvc_ctx->draw_indexed(id_buff->list_size, 0, 0);

		shadow_swap_chain->present(); //render all prepared stuff

	}

	void release() {

		buff->release();
		delete buff;

		id_buff->release();
		delete id_buff;
	}

	vertex_buffer* buff;
	index_buffer* id_buff;

public:

	float delta_scale;
	float delta_pos;

	float  delta_time;
	long old_delta_time;
	long new_delta_time;

public:

    matrix world_cam;
};