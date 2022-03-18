#version 460 core

uniform float col;

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(1., col, 0., 1.);
}