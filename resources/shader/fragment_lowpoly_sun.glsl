#version 460 core

in VTF
{
	vec3 v_color;
	vec3 v_normal;
	vec2 v_coord;
	vec3 world_pos;
};

layout (binding = 0) uniform sampler2D texture_diffuse1;

struct Light
{
	vec3 position;

	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};
uniform Light light;


layout (location = 0) out vec4 color;



void main()
{
	vec3 ambiant = light.ambiant * texture(texture_diffuse1, v_coord).rgb;
	
	color = vec4(ambiant, 1.0);
}