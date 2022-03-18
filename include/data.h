#ifndef DATA_H
#define DATA_H

#include <glm.hpp>
#include <vector>


const std::vector<glm::vec3> vertices
{
	glm::vec3(-.5, -.5, .5),
	glm::vec3(-.5, -.5, -.5),
	glm::vec3(.5, -.5, -.5),
	glm::vec3(.5, -.5, .5),
	glm::vec3(-.5, .5, .5),
	glm::vec3(-.5, .5, -.5),
	glm::vec3(.5, .5, -.5),
	glm::vec3(.5, .5, .5),
};

const std::vector<glm::vec3> colors
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

const std::vector<glm::uvec3> indices
{
	// Lateral faces
	glm::uvec3(0, 1, 5),
	glm::uvec3(0, 5, 4),
	glm::uvec3(1, 2, 6),
	glm::uvec3(1, 6, 5),
	glm::uvec3(2, 3, 7),
	glm::uvec3(2, 7, 6),
	glm::uvec3(3, 0, 4),
	glm::uvec3(3, 4, 7),

	// Top & bottom
	glm::uvec3(7, 4, 5),
	glm::uvec3(7, 5, 6),
	glm::uvec3(3, 1, 0),
	glm::uvec3(3, 2, 1),
};



#endif