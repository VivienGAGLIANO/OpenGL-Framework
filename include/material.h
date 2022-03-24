#ifndef MATERIAL_H
#define MATERIAL_H

#include "pipeline.h"
#include "texture.h"


class Material
{
public:
	explicit Material(const Texture* texture);
	explicit Material(const Pipeline& pipeline);
	explicit Material(const char *vertex_path = "resources/shader/vertex.glsl", const char* fragment_path = "resources/shader/fragment.glsl");
	explicit Material(const Texture* texture, const char* vertex_path = "resources/shader/vertex.glsl",
	                  const char* fragment_path = "resources/shader/fragment.glsl");
	void prepare() const;


private:
	Pipeline pipeline;
	Texture *texture = nullptr;
};

#endif