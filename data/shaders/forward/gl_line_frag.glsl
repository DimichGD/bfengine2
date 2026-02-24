#version 460 core
#pragma shader_stage(fragment)

layout(std140, set = 0, binding = 2) uniform Colors
{
	vec4 U_COLORS[4];
};

/*layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(location = 1) uniform int U_MATERIAL_INDEX;

layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLORS[U_MATERIAL_INDEX];
}
