#ifndef MESH_H
#define MESH_H

#include <glm.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

#include "pipeline.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

private:
	void prepare_for_render(Pipeline &pipeline);
	void set_buffer_objects();

	GLuint vao, vbo, ebo;
};

#endif