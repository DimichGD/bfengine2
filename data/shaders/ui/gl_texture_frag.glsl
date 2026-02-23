#version 460 core
#pragma shader_stage(fragment)

layout(std140, binding = 1) uniform Colors
{
	vec4 U_COLORS[4];
};

layout(binding = 0) uniform sampler2D diffuse_map;

/*layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLORS[0] * texture(diffuse_map, TEXCOORD_0).r; //vec4(1.0, 1.0, 1.0, texture(diffuse_map, TEXCOORD_0).r);
}
