#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm.hpp>
#include <vector>
#include <assimp/scene.h>

#include "mesh.h"


class Model
{
public:
	explicit Model(const char *path);
	// long n_elements() const;
	// void prepare() const;


private:
	std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, const char *typeName);
	void load_model(const char* path);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	void process_node(aiNode* node, const aiScene* scene);

	std::vector<Mesh> meshes;


	// void set_buffer_objects();

	// std::vector<glm::uvec3> indices;
	// std::vector<Vertex> vertices;
	// GLuint vao, ibo, vbo, ubo, nbo;
};

#endif