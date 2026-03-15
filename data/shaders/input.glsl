#ifdef UNIFORM_PROJ_VIEW
layout(std140, set = 0, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
	mat4 U_VIEW_MATRIX;
};

#endif

#ifdef UNIFORM_PROJ
layout(std140, set = 0, binding = 0) uniform Camera
{
	mat4 U_PROJ_MATRIX;
};

#endif

#ifdef UNIFORM_MODEL_MATRICES
layout(std430, set = 0, binding = 1) buffer readonly Matrices
{
	mat4 U_MODEL_MATRICES[];
};

#endif

#ifdef UNIFORM_COLORS
layout(std140, set = 0, binding = 2) uniform Colors
{
	vec4 U_COLORS[32];
};

#endif

#ifdef UNIFORM_CAMERA_DATA
layout(std140, set = 0, binding = 3) uniform CameraData
{
	mat4 U_INV_PROJ_MATRIX;
	mat4 U_INV_VIEW_MATRIX;
	vec4 U_CAMERA_POS;
};

#endif

#ifdef UNIFORM_POINT_LIGHTS
layout(std140, set = 0, binding = 4) uniform Lights
{
	vec4 U_POINT_LIGHTS[32];
};

#endif

#ifdef CONSTANT_OBJECT_INDEX
layout(push_constant) uniform Constants
{
	layout(offset = 0) int U_OBJECT_INDEX;
};

#endif

#ifdef CONSTANT_MATERIAL_INDEX
layout(push_constant) uniform Constants
{
	layout(offset = 4) int U_MATERIAL_INDEX;
};

#endif
