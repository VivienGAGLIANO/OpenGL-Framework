#version 460 core

in VTF
{
	vec3 v_color;
};

layout (location = 0) out vec4 color;


void main()
{
	color = vec4(v_color, 1.);
}