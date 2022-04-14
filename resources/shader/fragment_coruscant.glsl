#version 460 core

in VTF
{
	vec3 v_color;
	vec3 v_normal;
	vec2 v_coord;
	vec3 world_pos;
};

layout (binding = 0) uniform sampler2D texture_diffuse1;
layout (binding = 1) uniform sampler2D texture_emission1;
layout (binding = 2) uniform sampler2D texture_metallic1;

struct Light
{
	vec3 position;

	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};
uniform Light light;

uniform vec3 cam_pos;


layout (location = 0) out vec4 color;

vec3 normal;
vec3 L;
vec3 V;


float compute_diffuse()
{
	return max(0.0, dot(normal, L)); 
}

float compute_specular()
{
	vec3 R = reflect(-L, normal);
	return pow(max(0, dot(R, V)), light.shininess);
}


void main()
{
	normal = normalize(v_normal);
	L = normalize(light.position - world_pos);
	V = normalize(cam_pos - world_pos);

	vec3 ambiant = light.ambiant * texture(texture_diffuse1, v_coord).rgb;
	vec3 diffuse = compute_diffuse() * light.diffuse * texture(texture_diffuse1, v_coord).rgb;
	vec3 specular = compute_specular() * light.specular * texture(texture_metallic1, v_coord).b;
	vec3 emission = texture(texture_emission1, v_coord).rgb;

	color = vec4(ambiant + diffuse + specular + emission, 1.0);
}