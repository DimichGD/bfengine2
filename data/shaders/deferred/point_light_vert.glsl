layout(location = 0) out vec2 SCREEN_POSITION;

void main()
{
	gl_Position = U_PROJ_MATRIX * U_VIEW_MATRIX * U_MODEL_MATRICES[U_OBJECT_INDEX] * vec4(IN_POSITION, 1.0);
	SCREEN_POSITION = gl_Position.xy / gl_Position.w;
}
