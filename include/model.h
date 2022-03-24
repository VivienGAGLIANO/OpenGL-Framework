#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <vector>
#include <glfw3.h>
//#include <glad/glad.h>


class Model
{
public:
	Model();
	long n_elements() const;
	void prepare() const;


private:
	void set_buffer_objects();

	std::vector<glm::uvec3> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint vao, ibo, vbo, ubo, nbo;
};

#endif