#version 460 core

/*layout(set = 1, binding = 0) uniform sampler2D U_TEXTURES[32];

layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(set = 1, binding = 0) uniform sampler2D diffuse_map;
layout(set = 1, binding = 1) uniform sampler2D normal_map;
layout(set = 1, binding = 2) uniform sampler2D specular_map;

layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 1) in vec3 NORMAL;
layout(location = 2) in vec3 BINORMAL;
layout(location = 3) in vec3 TANGENT;

layout(location = 0) out vec4 OUT_COLOR_0;
layout(location = 1) out vec4 OUT_COLOR_1;
layout(location = 2) out vec4 OUT_COLOR_2;

void main()
{
	vec4 D = texture(diffuse_map, TEXCOORD_0);
	vec3 N = texture(normal_map, TEXCOORD_0).xyz;
	vec4 S = texture(specular_map, TEXCOORD_0);
	
	/*vec4 D = texture(U_TEXTURES[U_MATERIAL_INDEX + 0], IN_TEXCOORD_0);
	vec3 N = texture(U_TEXTURES[U_MATERIAL_INDEX + 1], IN_TEXCOORD_0).xyz;
	vec4 S = texture(U_TEXTURES[U_MATERIAL_INDEX + 2], IN_TEXCOORD_0);*/
	
	N = normalize(N * 2.0 - 1.0);
	N.x = -N.x;
	mat3 TBN = mat3(normalize(TANGENT), normalize(BINORMAL), normalize(NORMAL));
	
	OUT_COLOR_0 = D;
	OUT_COLOR_1 = vec4(TBN * N, 1.0);
	OUT_COLOR_2 = S;
}
