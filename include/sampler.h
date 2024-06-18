#ifndef SAMPLER_H
#define SAMPLER_H

#include <glad/glad.h>
#include <string>

// TODO implement sampler re-use architecture
class Sampler
{
public:
	Sampler(const std::string& name);
	~Sampler();

	GLuint get_id() const;

protected:
	GLuint id;
	std::string name;
};


class DefaultSampler : public Sampler
{
public:
	DefaultSampler(const std::string& name = "default_sampler");
};

#endif // SAMPLER_H