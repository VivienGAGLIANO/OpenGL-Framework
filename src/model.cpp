#include "model.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


Model::Model(const char* path)
{
	load_model(path);
}

//long Model::n_elements() const
//{
//	return 3 * indices.size();
//}

//void Model::prepare() const
//{
//	glBindVertexArray(vao);
//}

void Model::load_model(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // other model processing options if needed, computing normals for example

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex v;

		glm::vec3 vector; // temp var because Assimp data don't convert well to glm

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		v.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		v.normal = vector;

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			v.uv = vec;
		}
		else
			v.uv = glm::vec2(0.0f, 0.0f);

		vertices.push_back(v);
	}

	// TODO : I was here
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	for (unsigned int m_mesh : node->mMeshes)
	{
		aiMesh *mesh = scene->mMeshes(m_mesh);
		meshes.push_back(process_mesh(mesh, scene));
	}

	for (aiNode *m_num_child : node->mChildren)
	{
		process_node(m_num_child, scene);
	}
}

//void Model::set_buffer_objects()
//{
//
//}
