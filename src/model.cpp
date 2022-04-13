#include "model.h"

#include <iostream>
#include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stb_image.h>



std::string file_name(const std::string& path)
{
	auto file = path.substr(path.find_last_of("/\\") + 1);
	return file.substr(0, file.find_last_of('.'));
}

Model::Model(const char* path)
{
	load_model(path);
}

std::vector<Mesh> Model::get_meshes() const
{
	return meshes;
}

std::vector<Texture> Model::load_material_textures(aiMaterial* mat, aiTextureType type, const char* type_name)
{	
	std::vector<Texture> textures;
	for (int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (int j = 0; !skip && j < Model::loaded_textures.size(); ++j)
			if (std::strcmp(loaded_textures[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(loaded_textures[j]);
				skip = true;
			}
		
		if (!skip)
		{
			Texture tex;
			tex.id = Model::texture_from_file(str.C_Str(), directory);
			tex.type = type_name;
			tex.path = str.C_Str();
			textures.push_back(tex);
			loaded_textures.push_back(tex);
		}
	}

	return textures;
}

//long Model::n_elements() const
//{
//	return 3 * indices.size();
//}

//void Model::prepare() const
//{
//	glBindVertexArray(vao);
//}

void Model::load_model(const std::string &path)
{
	Assimp::Importer importer;
	auto logger = Assimp::DefaultLogger::create((std::string ("log/assimp/") + file_name(path) + std::string("Log.txt")).c_str(), Assimp::Logger::VERBOSE);
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_PreTransformVertices | aiProcess_ValidateDataStructure | aiProcess_OptimizeMeshes /*| aiProcess_OptimizeGraph | aiProcess_EmbedTextures*/); // other model processing options if needed, computing normals for example

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	process_node(scene->mRootNode, scene);
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

	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0) // > 0 ??
	{
		// TODO : handle all texture types
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuse_maps = load_material_textures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_maps.cbegin(), diffuse_maps.cend());
		std::vector<Texture> specular_maps = load_material_textures(mat, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specular_maps.cbegin(), specular_maps.cend());
		std::vector<Texture> normal_maps = load_material_textures(mat, aiTextureType_NORMALS, "texture_normals");
		textures.insert(textures.end(), normal_maps.cbegin(), normal_maps.cend());

		auto met = load_material_textures(mat, aiTextureType_TRANSMISSION, "texture_transmission");
		textures.insert(textures.end(), met.cbegin(), met.cend());

		// aiString fs;
		// if (AI_SUCCESS == mat->Get(AI_MATKEY_SHADER_FRAGMENT, fs))
		// 	std::cout << "kboom\n";
	}

	return Mesh(vertices, indices, textures);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(process_mesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		process_node(node->mChildren[i], scene);
	}
}

unsigned Model::texture_from_file(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}