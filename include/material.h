#ifndef MATERIAL_H
#define MATERIAL_H

#include "pipeline.h"
#include "TextureOld.h"


class Material
{
public:
	explicit Material(const TextureOld* texture);
	explicit Material(const Pipeline& pipeline);
	explicit Material(const char *vertex_path = "resources/shader/vertex.glsl", const char* fragment_path = "resources/shader/fragment.glsl");
	explicit Material(const TextureOld* texture, const char* vertex_path = "resources/shader/vertex.glsl",
	                  const char* fragment_path = "resources/shader/fragment.glsl");
	~Material();
	Pipeline get_pipeline();
	void prepare() const;



private:
	Pipeline pipeline;
	TextureOld *texture = nullptr;
};

#endif