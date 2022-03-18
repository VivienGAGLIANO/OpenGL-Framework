#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 mvp;

out gl_PerVertex
{
	vec4 gl_Position;
};


void main()
{
	gl_Position = mvp * vec4(position, 1.0);
}