#include "material.h"

Material::Material(const Texture* texture) : Material()
{
	*this->texture = *texture;
}

Material::Material(const Pipeline& pipeline) : pipeline(pipeline)
{
}

Material::Material(const char* vertex_path, const char* fragment_path) : pipeline(Pipeline(vertex_path, fragment_path))
{
}

Material::Material(const Texture* texture, const char* vertex_path, const char* fragment_path) : pipeline(Pipeline(vertex_path, fragment_path))
{
	pipeline.use_pipeline();
	*this->texture = *texture;
}

void Material::prepare() const
{
	pipeline.use_pipeline();
}
