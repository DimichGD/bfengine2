layout(location = 0) out vec2 TEXCOORD_0;
layout(location = 1) out vec3 NORMAL;
layout(location = 2) out vec3 BINORMAL;
layout(location = 3) out vec3 TANGENT;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	
	NORMAL = IN_NORMAL;
	BINORMAL = cross(IN_NORMAL, IN_TANGENT.xyz) * IN_TANGENT.w;
	TANGENT = IN_TANGENT.xyz;
	
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
}
