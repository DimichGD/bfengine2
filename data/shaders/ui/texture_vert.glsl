#version 450 core
layout(location = 0) in vec2 IN_POSITION;
layout(location = 1) in vec2 IN_TEXCOORD_0;

layout(location = 2) uniform mat4 PROJ_MATRIX;

out vec2 TEXCOORD_0;

void main()
{
	TEXCOORD_0 = IN_TEXCOORD_0;
	gl_Position = PROJ_MATRIX * vec4(IN_POSITION, 0.0, 1.0);
}
