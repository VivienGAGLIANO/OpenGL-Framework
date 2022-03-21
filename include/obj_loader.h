#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glm.hpp>
#include <iostream>
#include <vector>


inline bool load_obj(
	const char * path, 
	std::vector<glm::vec3> &vertices, 
	std::vector<glm::vec2> &uvs, 
	std::vector<glm::vec3> &normals)
{
	std::vector< unsigned int > vertex_indices, uv_indices, normal_indices;
	std::vector< glm::vec3 > tmp_vertices;
	std::vector< glm::vec2 > tmp_uvs;
	std::vector< glm::vec3 > tmp_normals;

	// Open file
	FILE* file;
	fopen_s(&file, path, "r");
	if (file == nullptr) 
	{
		std::cout << "Unable to open file at " << path << std::endl;
		return false;
	}

	// Read file
	while (1) 
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			tmp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tmp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertex_indices.push_back(vertexIndex[0]);
			vertex_indices.push_back(vertexIndex[1]);
			vertex_indices.push_back(vertexIndex[2]);
			uv_indices.push_back(uvIndex[0]);
			uv_indices.push_back(uvIndex[1]);
			uv_indices.push_back(uvIndex[2]);
			normal_indices.push_back(normalIndex[0]);
			normal_indices.push_back(normalIndex[1]);
			normal_indices.push_back(normalIndex[2]);
		}
	}

	vertices.clear();
	uvs.clear();
	normals.clear();

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertex_indices.size(); i++)
	{
		vertices.push_back(tmp_vertices.at(vertex_indices[i] - 1));
		uvs.push_back(tmp_uvs.at(uv_indices[i] - 1));
		normals.push_back(tmp_normals.at(normal_indices[i] - 1));
	}

	return true;
}

#endif
