#version 460 core

in VTF
{
	vec3 v_color;
	vec3 v_normal;
	vec2 v_coord;
	vec3 world_pos;
};

layout (binding = 0) uniform sampler2D texture_diffuse1;
layout (binding = 2) uniform sampler2D texture_specular1;
layout (binding = 1) uniform sampler2D texture_transmission1;
uniform vec3 light_pos;

layout (location = 0) out vec4 color;

// TODO add normals here maybe
// also compute local illumination probably

void main()
{
	color = texture(texture_diffuse1, v_coord);
	// color = vec4(v_color, 1.);
}