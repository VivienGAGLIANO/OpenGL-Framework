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
	std::vector<Mesh> get_meshes() const;

	// long n_elements() const;
	// void prepare() const;


private:
	std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, const char* type_name);
	void load_model(const std::string& path);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	void process_node(aiNode* node, const aiScene* scene);
	static unsigned int texture_from_file(const char* path, const std::string& directory);

	inline static std::vector<Texture> loaded_textures = std::vector<Texture>();
	std::string directory;
	std::vector<Mesh> meshes;


	// void set_buffer_objects();

	// std::vector<glm::uvec3> indices;
	// std::vector<Vertex> vertices;
	// GLuint vao, ibo, vbo, ubo, nbo;
};

#endif