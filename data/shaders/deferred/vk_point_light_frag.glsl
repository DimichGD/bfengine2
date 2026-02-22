#version 460 core
#pragma shader_stage(fragment)

layout(set = 1, binding = 0) uniform sampler2D diffuse_map;
layout(set = 1, binding = 1) uniform sampler2D normal_map;
layout(set = 1, binding = 2) uniform sampler2D specular_map;
layout(set = 1, binding = 3) uniform sampler2D position_map;
layout(set = 1, binding = 4) uniform sampler2D depth_map;

layout(std140, set = 0, binding = 2) uniform Lights
{
	vec4 U_POINT_LIGHTS[1];
};

layout(std140, set = 0, binding = 3) uniform Camera2
{
	mat4 U_INV_PROJ_MATRIX;
	mat4 U_INV_VIEW_MATRIX;
	vec4 U_CAMERA_POS;
};

layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};

layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 1) in vec3 POSITION;
layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	vec4 ndc = vec4(
		POSITION.xy,
		texelFetch(depth_map, ivec2(gl_FragCoord.xy), 0).r,
		1.0
	);
	
	vec4 view_pos = U_INV_PROJ_MATRIX * ndc;
	vec3 world_pos = vec3(U_INV_VIEW_MATRIX * vec4(view_pos.xyz / view_pos.w, 1.0));
	vec2 tex_coord = POSITION.xy * 0.5 + 0.5;
	//tex_coord.y = -tex_coord.y;
	
	vec3 diffuse = texture(diffuse_map, tex_coord).xyz;
	//vec3 diffuse = texelFetch(diffuse_map, ivec2(gl_FragCoord.xy), 0).xyz;
	vec3 normal = texture(normal_map, tex_coord).xyz;
	vec3 specular = texture(specular_map, TEXCOORD_0).xyz;
	vec3 position = texture(position_map, TEXCOORD_0).xyz;
	
	vec3 light_pos = U_POINT_LIGHTS[U_MATERIAL_INDEX].xyz;
	float radius = U_POINT_LIGHTS[U_MATERIAL_INDEX].w;
	
	vec3 L = normalize(light_pos - world_pos);
	//vec3 N = normalize(normal * 2.0 - vec3(1.0));
	vec3 N = normalize(normal);
	float D = max(dot(N, L), 0.0);
	vec3 V = normalize(U_CAMERA_POS.xyz - world_pos);
	vec3 H = normalize(L + V);
	vec3 R = reflect(-L, N);
	float S = pow(max(dot(N, H), 0.0), 32.0);
	//float S = pow(max(dot(V, R), 0.0), 16.0);

	OUT_COLOR = vec4(diffuse * D + specular * S * 4.0, 1.0);
	//OUT_COLOR = vec4(D);
}
