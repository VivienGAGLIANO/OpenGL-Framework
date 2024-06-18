#include "sampler.h"


Sampler::Sampler(const std::string& name) :
	name(name)
{
	glCreateSamplers(1, &id);
}

Sampler::~Sampler()
{
	glDeleteSamplers(1, &id);
}

GLuint Sampler::get_id() const
{
	return id;
}


DefaultSampler::DefaultSampler(const std::string& name) :
	Sampler(name)
{
	glSamplerParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}