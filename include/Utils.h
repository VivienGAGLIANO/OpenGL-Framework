#include "scene.h"
#include <stdio.h> 

glm::vec3 operator_multiply(glm::vec3 vector, float d);
glm::vec3 operator_divide(glm::vec3 vector, float n);
glm::vec3 computeDirection(glm::vec3 p1, glm::vec3 p2);

float computeDistance(glm::vec3 p1, glm::vec3 p2);