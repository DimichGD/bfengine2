#version 460 core

layout(location = 0) in vec3 IN_POSITION;

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

void main()
{
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
}
