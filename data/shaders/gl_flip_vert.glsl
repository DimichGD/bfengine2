#version 460 core
#pragma shader_stage(vertex)

layout(location = 0) in vec3 IN_POSITION;
layout(location = 1) in vec2 IN_TEXCOORD_0;

layout(std140, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
};

layout(location = 0) out vec2 TEXCOORD_0;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	gl_Position = U_PROJ_MATRIX * vec4(IN_POSITION, 1.0);
}
