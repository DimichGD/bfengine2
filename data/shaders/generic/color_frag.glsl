layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLORS[U_MATERIAL_INDEX];
}
