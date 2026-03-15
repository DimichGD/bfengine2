#version 460 core

layout(std140, set = 0, binding = 3) uniform CameraData
{
	mat4 U_INV_PROJ_MATRIX;
	mat4 U_INV_VIEW_MATRIX;
	vec4 U_CAMERA_POS;
};

layout(std140, set = 0, binding = 4) uniform Lights
{
	vec4 U_POINT_LIGHTS[32];
};

layout(set = 1, binding = 0) uniform sampler2D diffuse_map;
layout(set = 1, binding = 1) uniform sampler2D normal_map;
layout(set = 1, binding = 2) uniform sampler2D specular_map;
layout(set = 1, binding = 3) uniform sampler2D depth_map;

layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};

layout(location = 0) in vec2 SCREEN_POSITION;
layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	/*vec4 result = vec4(0.0);
	for (int i = 0; i < 4; i++)
	{
		vec4 ndc = vec4(
			SCREEN_POSITION,
			texelFetch(depth_map, ivec2(gl_FragCoord.xy), i).r,
			1.0
		);
		
		vec4 view_pos = U_INV_PROJ_MATRIX * ndc;
		vec3 world_pos = vec3(U_INV_VIEW_MATRIX * vec4(view_pos.xyz / view_pos.w, 1.0));

		vec3 diffuse  = texelFetch(diffuse_map,  ivec2(gl_FragCoord.xy), i).xyz;
		vec3 normal   = texelFetch(normal_map,   ivec2(gl_FragCoord.xy), i).xyz;
		vec3 specular = texelFetch(specular_map, ivec2(gl_FragCoord.xy), i).xyz;

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

		result += att * vec4(diffuse * D + specular * S, 1.0);
	}
	
	OUT_COLOR = result / 4.0;*/
	
	vec4 ndc = vec4(
		SCREEN_POSITION,
		texelFetch(depth_map, ivec2(gl_FragCoord.xy), 0).r,
		1.0
	);
	
	vec4 view_pos = U_INV_PROJ_MATRIX * ndc;
	vec3 world_pos = vec3(U_INV_VIEW_MATRIX * vec4(view_pos.xyz / view_pos.w, 1.0));

	vec3 diffuse  = texelFetch(diffuse_map,  ivec2(gl_FragCoord.xy), 0).xyz;
	vec3 normal   = texelFetch(normal_map,   ivec2(gl_FragCoord.xy), 0).xyz;
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
	//OUT_COLOR = vec4(normal, 1.0);
}
