#version 460 core

in VTF
{
	vec3 v_color;
	vec2 v_coord;
};

uniform sampler2D tex;

layout (location = 0) out vec4 color;


void main()
{
	color = texture(tex, v_coord); // vec4(v_color, 1.);
}