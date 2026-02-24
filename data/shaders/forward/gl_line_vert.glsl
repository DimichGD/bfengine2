#version 460 core
#pragma shader_stage(vertex)

layout(location = 0) in vec3 IN_POSITION;

layout(std140, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
	mat4 U_VIEW_MATRIX;
};

layout(std140, binding = 1) uniform Matrices
{
	mat4 U_MODEL_MATRICES[32];
};

layout(location = 0) uniform int U_OBJECT_INDEX;

void main()
{
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
}
