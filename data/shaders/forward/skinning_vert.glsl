INPUT_POSITION;
INPUT_TEXCOORD_0;
INPUT_NORMAL;
INPUT_TANGENT;
INPUT_BONES;
INPUT_WEIGHTS;

UNIFORM_MODEL_MATRIX;
UNIFORM_VIEW_MATRIX;
UNIFORM_PROJ_MATRIX;

layout(std140, binding = 0) uniform ModelMatrices
{
	mat4 matrices[128];
};

layout(std140, binding = 1) uniform BoneMatrices
{
	mat4 bones[128];
};

out vec2 TEXCOORD_0;

void main()
{
	mat4 matrix = bones[int(IN_BONES.x)] * IN_WEIGHTS.x;
		matrix += bones[int(IN_BONES.y)] * IN_WEIGHTS.y;
		matrix += bones[int(IN_BONES.z)] * IN_WEIGHTS.z;
		matrix += bones[int(IN_BONES.w)] * IN_WEIGHTS.w;
	
	TEXCOORD_0 = IN_TEXCOORD_0;
	gl_Position = PROJ_MATRIX * VIEW_MATRIX * matrices[gl_BaseInstance] * matrix * vec4(IN_POSITION, 1.0);
}
