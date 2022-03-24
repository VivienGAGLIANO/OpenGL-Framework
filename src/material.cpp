#include "material.h"

void Material::prepare() const
{
	pipeline.use_pipeline();
}
