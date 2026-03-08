layout(location = 0) out vec2 TEXCOORD_0;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	gl_Position = U_PROJ_MATRIX * vec4(IN_POSITION, 1.0);
}
