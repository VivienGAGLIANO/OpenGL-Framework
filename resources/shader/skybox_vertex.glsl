#version 460 core


layout (location = 0) in vec3 position;

uniform mat4 v, p;

out VTF
{
	vec3 v_coord;
};

out gl_PerVertex
{
	vec4 gl_Position;
};


void main()
{
	v_coord = position;
	gl_Position = p * v * vec4(position, 1.0);
}