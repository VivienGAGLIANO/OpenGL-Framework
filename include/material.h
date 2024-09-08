#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "pipeline.h"
#include "sampler.h"
#include "shader_program.h"


class Material
{
public:
	explicit Material(const std::string &vertex_path, const std::string& fragment_path, std::shared_ptr<Sampler> sampler);
	~Material();
	
	Program& get_program();
	void prepare() const;

	std::shared_ptr<Sampler> sampler;

private:
	Program render_program;
};

#endif