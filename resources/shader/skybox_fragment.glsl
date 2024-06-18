#version 460 core


in VTF
{
	vec3 v_coord;
};

layout (binding = 0) uniform samplerCube skybox;

layout (location = 0) out vec4 color;


void main()
{
	color = texture(skybox, v_coord);
}