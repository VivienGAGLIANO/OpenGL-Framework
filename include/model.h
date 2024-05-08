#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <vector>

#include "mesh.h"


class Model
{
public:
	explicit Model(const char *path);
	std::vector<Mesh> get_meshes() const;


private:
	std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, const char* type_name);
	void load_model(const std::string& path);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	void process_node(aiNode* node, const aiScene* scene);
	static unsigned int texture_from_file(const char* path, const std::string& directory);

	inline static std::vector<Texture> loaded_textures = std::vector<Texture>();
	std::string directory;
	std::vector<Mesh> meshes;
};

#endif