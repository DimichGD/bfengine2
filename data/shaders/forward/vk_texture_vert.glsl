#version 460 core
#pragma shader_stage(vertex)

layout(location = 0) in vec3 IN_POSITION;
layout(location = 1) in vec2 IN_TEXCOORD_0;

layout(std140, set = 0, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
	mat4 U_VIEW_MATRIX;
};

layout(std140, set = 0, binding = 1) uniform Matrices
{
	mat4 U_MODEL_MATRICES[32];
};

layout(push_constant) uniform Constants
{
	layout(offset = 0) int U_OBJECT_INDEX;
};

layout(location = 0) out vec2 TEXCOORD_0;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
	
#ifdef VULKAN
	gl_Position.y = -gl_Position.y;
#endif
}
