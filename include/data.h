#ifndef DATA_H
#define DATA_H

#include <glm.hpp>
#include <vector>


std::vector<glm::vec3> vertices
{
	glm::vec3(-.7, -.7, .7),
	glm::vec3(-.5, -.5, -.5),
	glm::vec3(.5, -.5, -.5),
	glm::vec3(.5, -.5, .5),
	glm::vec3(-.5, .5, .5),
	glm::vec3(-.5, .5, -.5),
	glm::vec3(.5, .5, -.5),
	glm::vec3(.5, .5, .5),
};

std::vector<glm::vec3> colors
{
	glm::vec3(0, 0, 0),
	glm::vec3(0, 1, 0),
	glm::vec3(1, 1, 0),
	glm::vec3(1, 0, 0),
	glm::vec3(0, 0, 1),
	glm::vec3(0, 1, 1),
	glm::vec3(1, 1, 1),
	glm::vec3(1, 0, 1),
};

std::vector<glm::vec2> uv_coords
{
	glm::vec2(.25f, 2.f / 3.f),
	glm::vec2(.25f, 1.f / 3.f),
	glm::vec2(0.f, 1.f / 3.f),
	glm::vec2(0.f, 2.f / 3.f),
	glm::vec2(.5f, 2.f / 3.f),
	glm::vec2(.5f, 1.f / 3.f),
	glm::vec2(.75f, 1.f / 3.f),
	glm::vec2(.75f, 2.f / 3.f)
};

std::vector<glm::vec3> normals;

std::vector<glm::uvec3> indices
{
	// Lateral faces
	glm::uvec3(1, 0, 5),
	glm::uvec3(5, 0, 4),
	glm::uvec3(2, 1, 6),
	glm::uvec3(6, 1, 5),
	glm::uvec3(3, 2, 7),
	glm::uvec3(7, 2, 6),
	glm::uvec3(0, 3, 4),
	glm::uvec3(4, 3, 7),

	// Top & bottom
	glm::uvec3(4, 7, 5),
	glm::uvec3(5, 7, 6),
	glm::uvec3(1, 3, 0),
	glm::uvec3(2, 3, 1),
};



#endif