#ifndef DATA_H
#define DATA_H

#include <glm.hpp>
#include <vector>


const std::vector<glm::vec3> vertices
{
	glm::vec3(-.5, -.5, 0),
	glm::vec3(0, .5, 0),
	glm::vec3(.5, -.5, 0)
};

const std::vector<glm::uvec3> indices
{
	glm::uvec3(0, 1, 2)
};



#endif