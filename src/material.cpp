#include "material.h"
#include "scene.h"


Material::Material(const std::string& vertex_path, const std::string& fragment_path, std::shared_ptr<Sampler> sampler) :
	render_program(Program(
		ShaderObject(vertex_path, GL_VERTEX_SHADER), 
		ShaderObject(fragment_path, GL_FRAGMENT_SHADER))),
	sampler(sampler)
{
}

Material::~Material()
{
}

Program Material::get_program() const
{
	return render_program;
}

void Material::prepare() const
{
	render_program.use_program();
}
