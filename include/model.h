#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm.hpp>
#include <vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};


class Model
{
public:
	Model();
	long n_elements() const;
	void prepare() const;


private:
	void set_buffer_objects();

	std::vector<glm::uvec3> indices;
	std::vector<Vertex> vertices;
	GLuint vao, ibo, vbo, ubo, nbo;
};

#endif