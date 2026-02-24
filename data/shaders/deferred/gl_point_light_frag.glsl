#version 460 core
#pragma shader_stage(fragment)

layout(std140, binding = 2) uniform Lights
{
	vec4 U_POINT_LIGHTS[1];
};

layout(std140, binding = 3) uniform Camera2
{
	mat4 U_INV_PROJ_MATRIX;
	mat4 U_INV_VIEW_MATRIX;
	vec4 U_CAMERA_POS;
	vec2 inv_viewport;
};

layout(binding = 0) uniform sampler2D diffuse_map;
layout(binding = 1) uniform sampler2D normal_map;
layout(binding = 2) uniform sampler2D specular_map;
layout(binding = 3) uniform sampler2D depth_map;

/*layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};*/

layout(location = 1) uniform int U_MATERIAL_INDEX;

layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	vec4 ndc = vec4(
		gl_FragCoord.xy * inv_viewport * 2.0 - 1.0,
		texelFetch(depth_map, ivec2(gl_FragCoord.xy), 0).r,
		1.0
	);
	
	vec4 view_pos = U_INV_PROJ_MATRIX * ndc;
	vec3 world_pos = vec3(U_INV_VIEW_MATRIX * vec4(view_pos.xyz / view_pos.w, 1.0));

	vec3 diffuse = texelFetch(diffuse_map, ivec2(gl_FragCoord.xy), 0).xyz;
	vec3 normal = texelFetch(normal_map, ivec2(gl_FragCoord.xy), 0).xyz;
	vec3 specular = texelFetch(specular_map, ivec2(gl_FragCoord.xy), 0).xyz;
	
	vec3 light_pos = U_POINT_LIGHTS[U_MATERIAL_INDEX].xyz;
	float radius = U_POINT_LIGHTS[U_MATERIAL_INDEX].w;
	
	vec3 L = normalize(light_pos - world_pos);
	//vec3 N = normalize(normal * 2.0 - vec3(1.0));
	vec3 N = normalize(normal);
	float D = max(dot(N, L), 0.0);
	vec3 V = normalize(U_CAMERA_POS.xyz - world_pos);
	vec3 H = normalize(L + V);
	vec3 R = reflect(-L, N);
	float S = pow(max(dot(N, H), 0.0), 32.0) * 4.0;
	//float S = pow(max(dot(V, R), 0.0), 16.0);
	
	float dist = length(light_pos - world_pos);
	//float att = clamp(1.0 - dist * dist / (radius * radius), 0.0, 1.0);
	float att = clamp(1.0 - dist / radius, 0.0, 1.0);

	OUT_COLOR = att * vec4(diffuse * D + specular * S, 1.0);
	//OUT_COLOR = vec4(1.0, 0.0, 0.0, 1.0);
	//OUT_COLOR = vec4(gl_FragCoord.xy / vec2(1280.0, 720.0) * 2.0 - 1.0, 0.0, 1.0);
	//OUT_COLOR = vec4(world_pos, 1.0);
}
