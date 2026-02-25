#version 460 core
#pragma shader_stage(vertex)

layout(location = 0) in vec3 IN_POSITION;
layout(location = 1) in vec2 IN_TEXCOORD_0;
layout(location = 4) in vec3 IN_NORMAL;
layout(location = 5) in vec4 IN_TANGENT;

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
layout(location = 1) out vec3 NORMAL;
layout(location = 2) out vec3 BINORMAL;
layout(location = 3) out vec3 TANGENT;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	
	NORMAL = IN_NORMAL;
	BINORMAL = cross(IN_NORMAL, IN_TANGENT.xyz) * IN_TANGENT.w;
	TANGENT = IN_TANGENT.xyz;
	
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
}
