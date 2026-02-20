#version 450 core
layout(location = 4) uniform sampler2D TEXTURE_0;

in vec2 TEXCOORD_0;

out vec4 OUT_COLOR;

void main()
{
	OUT_COLOR = texture(TEXTURE_0, TEXCOORD_0);
}
