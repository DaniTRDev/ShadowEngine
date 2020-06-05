#pragma once
#include "pch.h"

class matrix {

public:

	matrix()
	{
	}

	void clear()
	{
		::memset(m_matrix, 0, sizeof(float) * 16);
		m_matrix[0][0] = 1;
		m_matrix[1][1] = 1;
		m_matrix[2][2] = 1;
		m_matrix[3][3] = 1;
	}

	void update_matrix_with_vec3(const vector_3d& translation)
	{
		m_matrix[3][0] = translation.x;
		m_matrix[3][1] = translation.y;
		m_matrix[3][2] = translation.z;
	}

	void set_scale(const vector_3d& scale)
	{
		m_matrix[0][0] = scale.x;
		m_matrix[1][1] = scale.y;
		m_matrix[2][2] = scale.z;
	}

	void operator *=(const matrix& a_matrix)
	{
		matrix out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_matrix[i][j] =
					m_matrix[i][0] * a_matrix.m_matrix[0][j] + m_matrix[i][1] * a_matrix.m_matrix[1][j] +
					m_matrix[i][2] * a_matrix.m_matrix[2][j] + m_matrix[i][3] * a_matrix.m_matrix[3][j];
			}
		}
		set_matrix(out);
	}

	void set_matrix(const matrix& a_matrix)
	{
		::memcpy(m_matrix, a_matrix.m_matrix, sizeof(float) * 16);
	}

	void set_ortho_lh(float width, float height, float near_plane, float far_plane)
	{
		m_matrix[0][0] = 2.0f / width;
		m_matrix[1][1] = 2.0f / height;
		m_matrix[2][2] = 1.0f / (far_plane - near_plane);
		m_matrix[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void set_x_rot(float x)
	{
		m_matrix[1][1] = cos(x);
		m_matrix[1][2] = sin(x);
		m_matrix[2][1] = -sin(x);
		m_matrix[2][2] = cos(x);
	}
	void set_y_rot(float y)
	{
		m_matrix[0][0] = cos(y);
		m_matrix[0][2] = -sin(y);
		m_matrix[2][0] = sin(y);
		m_matrix[2][2] = cos(y);
	}
	void set_z_rot(float z)
	{
		m_matrix[0][0] = cos(z);
		m_matrix[0][1] = sin(z);
		m_matrix[1][0] = -sin(z);
		m_matrix[1][1] = cos(z);
	}

	float get_det()
	{
		vector_4d minor, v1, v2, v3;
		float det;

		v1 = vector_4d(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[3][0]);
		v2 = vector_4d(m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[3][1]);
		v3 = vector_4d(m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2]);


		minor.cross(v1, v2, v3);
		det = -(m_matrix[0][3] * minor.x + m_matrix[1][3] * minor.y + m_matrix[2][3] * minor.z +
			m_matrix[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		matrix out;
		vector_4d v, vec[3];
		float det = 0.0f;

		det = get_det();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (m_matrix[j][0]);
					vec[a].y = (m_matrix[j][1]);
					vec[a].z = (m_matrix[j][2]);
					vec[a].w = (m_matrix[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_matrix[0][i] = pow(-1.0f, i) * v.x / det;
			out.m_matrix[1][i] = pow(-1.0f, i) * v.y / det;
			out.m_matrix[2][i] = pow(-1.0f, i) * v.z / det;
			out.m_matrix[3][i] = pow(-1.0f, i) * v.w / det;
		}

		set_matrix(out);
	}

	vector_3d get_z_dir()
	{
		return vector_3d(m_matrix[2][0], m_matrix[2][1], m_matrix[2][2]);
	}
	vector_3d get_x_dir()
	{
		return vector_3d(m_matrix[0][0], m_matrix[0][1], m_matrix[0][2]);
	}
	vector_3d get_vect3_trans()
	{
		return vector_3d(m_matrix[3][0], m_matrix[3][1], m_matrix[3][2]);
	}

	void set_perspective_fov_lh(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_matrix[0][0] = xscale;
		m_matrix[1][1] = yscale;
		m_matrix[2][2] = zfar / (zfar - znear);
		m_matrix[2][3] = 1.0f;
		m_matrix[3][2] = (-znear * zfar) / (zfar - znear);
	}

	float m_matrix[4][4] = {};

};