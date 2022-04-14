# version 460 core

in VTF
{
	vec3 v_color;
	vec3 v_normal;
	vec2 v_coord;
	vec3 world_pos;
};

layout (binding = 0) uniform sampler2D texture_diffuse1;
layout (binding = 1) uniform sampler2D texture_emission1;


layout (location = 0) out vec4 color;


void main()
{
	vec4 diffuse = texture(texture_diffuse1, v_coord);
	vec4 emission = texture(texture_emission1, v_coord);

	color = diffuse + emission;
}