#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv_coord;
layout (location = 3) in vec3 color;

uniform mat4 m, v, p;

out VTF
{
	layout(location = 0) vec3 v_color;
	layout(location = 1) vec3 v_normal;
	layout(location = 2) vec2 v_coord;
	layout(location = 3) vec3 world_pos;
};

out gl_PerVertex
{
	vec4 gl_Position;
};


void main()
{
	gl_Position = p * v * m * vec4(position, 1.0);
	v_color = color;
	v_normal = normal;
	v_coord = uv_coord;
	world_pos = (m * vec4(position, 1.0)).xyz;
}