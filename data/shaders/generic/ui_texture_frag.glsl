#version 460 core

layout(std140, set = 0, binding = 2) uniform Colors
{
	vec4 U_COLORS[32];
};

layout(set = 1, binding = 0) uniform sampler2D diffuse_map;

layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};

layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLORS[U_MATERIAL_INDEX] * texture(diffuse_map, TEXCOORD_0).r;
}
