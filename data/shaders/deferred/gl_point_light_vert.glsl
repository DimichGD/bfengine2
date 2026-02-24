#version 460 core
#pragma shader_stage(vertex)

layout(location = 0) in vec3 IN_POSITION;
//layout(location = 1) in vec2 IN_TEXCOORD_0;

layout(std140, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
	mat4 U_VIEW_MATRIX;
};

/*layout(std140, set = 0, binding = 1) uniform Matrices
{
	mat4 U_MODEL_MATRICES[32];
};*/

layout(std140, binding = 2) uniform Lights
{
	vec4 U_POINT_LIGHTS[1];
};

/*layout(push_constant) uniform Constants
{
	layout(offset = 0) int U_OBJECT_INDEX;
	//layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(location = 0) uniform int U_OBJECT_INDEX;

//layout(location = 0) out vec2 POSITION;

void main()
{
	//TEXCOORD_0 = IN_TEXCOORD_0;
	vec3 offset = U_POINT_LIGHTS[U_OBJECT_INDEX].xyz;
	float radius = U_POINT_LIGHTS[U_OBJECT_INDEX].w;
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * /*U_MODEL_MATRICES[U_OBJECT_INDEX] **/ vec4((IN_POSITION + offset) * radius, 1.0);
	//POSITION = gl_Position.xy;
}
