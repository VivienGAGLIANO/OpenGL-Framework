#ifndef MATERIAL_H
#define MATERIAL_H

#include "pipeline.h"


class Material
{
public:
	explicit Material(const Pipeline& pipeline);
	explicit Material(const char *vertex_path = "resources/shader/vertex.glsl", const char* fragment_path = "resources/shader/fragment.glsl");
	~Material();
	Pipeline get_pipeline() const;
	void prepare() const;


private:
	Pipeline pipeline;
};

#endif