struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

cbuffer constant_buffer_decl: register(b0) {

	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_project;
	unsigned int m_time;

}

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT vs_main(VS_INPUT input) {

	VS_OUTPUT output = (VS_OUTPUT)0;

	//WORLD SPACE
	output.position = mul(input.position, m_world);
	//VIEW SPACE
	output.position = mul(output.position, m_view);
	//SCREEN SPACE
	output.position = mul(output.position, m_project);

	output.color = input.color;

	return output;

}