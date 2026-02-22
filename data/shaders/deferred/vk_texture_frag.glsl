#version 460 core
#pragma shader_stage(fragment)

layout(set = 1, binding = 0) uniform sampler2D diffuse_map;
layout(set = 1, binding = 1) uniform sampler2D normal_map;
layout(set = 1, binding = 2) uniform sampler2D specular_map;
layout(set = 1, binding = 3) uniform sampler2D position_map;

layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 1) in vec3 POSITION;
//layout(location = 2) in mat3 TBN;
layout(location = 2) in vec3 NORMAL;
layout(location = 3) in vec3 BINORMAL;
layout(location = 4) in vec3 TANGENT;
//layout(location = 5) in mat3 TBN;

layout(location = 0) out vec4 OUT_COLOR_0;
layout(location = 1) out vec4 OUT_COLOR_1;
layout(location = 2) out vec4 OUT_COLOR_2;
layout(location = 3) out vec4 OUT_COLOR_3;

void main()
{
	vec4 D = texture(diffuse_map, TEXCOORD_0);
	vec3 N = normalize(texture(normal_map, TEXCOORD_0).xyz * 2.0 - 1.0);
	vec4 S = texture(specular_map, TEXCOORD_0);
	vec4 P = vec4(POSITION, 1.0);
	
	//
	N.x = -N.x;
	mat3 TBN = mat3(normalize(TANGENT), normalize(BINORMAL), normalize(NORMAL));
	
	OUT_COLOR_0 = D;
	OUT_COLOR_1 = vec4(TBN * N, 1.0);
	OUT_COLOR_2 = S;
	OUT_COLOR_3 = P;
	
	//OUT_COLOR_1 = vec4(BINORMAL, 1.0);
}
