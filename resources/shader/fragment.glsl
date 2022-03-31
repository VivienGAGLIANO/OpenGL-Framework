#version 460 core

in VTF
{
	vec3 v_color;
	vec3 v_normal;
	vec2 v_coord;
	vec3 world_pos;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 light_pos;

layout (location = 0) out vec4 color;

// TODO add normals here maybe
// also compute local illumination probably

void main()
{
	color = texture(texture_diffuse1, v_coord); // vec4(v_color, 1.);
}