#version 460 core

layout(std140, set = 1, binding = 0) uniform Colors
{
	vec4 U_COLOR;
};

/*layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLOR;
}
