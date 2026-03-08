layout(location = 0) in vec2 TEXCOORD_0;
layout(location = 0) out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = U_COLORS[U_MATERIAL_INDEX] * texture(diffuse_map, TEXCOORD_0).r;
}
