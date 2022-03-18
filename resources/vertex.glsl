#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 m, v, p;

out VTF
{
	vec3 v_color;
};

out gl_PerVertex
{
	vec4 gl_Position;
};


void main()
{
	gl_Position = p * v * m * vec4(position, 1.0);
	v_color = color;
}