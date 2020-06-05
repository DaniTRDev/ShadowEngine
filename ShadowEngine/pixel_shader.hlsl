struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant_buffer_decl: register(b0) {

	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_project;
	unsigned int m_time;

}

float4 ps_main(PS_INPUT input) : SV_TARGET
{
	return float4(lerp(input.color, float3(1, 1, 1), (float)((sin((float)(m_time / (float)500.0f)) + 1.0f) / 2.0f)), 1.0f);

}