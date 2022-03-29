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
	void prepare_for_render(Pipeline pipeline);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	inline static std::vector<Texture> loaded_textures = std::vector<Texture>();

private:
	void set_buffer_objects();

	GLuint vao, vbo, ebo;
};

#endif