#ifndef MATERIAL_H
#define MATERIAL_H

#include "pipeline.h"
#include "texture.h"


class Material
{
public:
	Material();
	void prepare() const;


private:
	Pipeline pipeline;
	Texture texture;
};

#endif