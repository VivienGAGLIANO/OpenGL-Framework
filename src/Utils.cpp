#include "Utils.h"

glm::vec3 operator_multiply(glm::vec3 vector, float n)
{
    float X = vector.x * n;
    float Y = vector.y * n;
    float Z = vector.z * n;
    return glm::vec3(X,Y,Z);
}

glm::vec3 operator_divide(glm::vec3 vector, float n)
{
    float X = vector.x / n;
    float Y = vector.y / n;
    float Z = vector.z / n;
    return glm::vec3(X,Y,Z);
}

glm::vec3 computeDirection(glm::vec3 p1, glm::vec3 p2)
{
    float x = p2.x - p1.x;
    float y = p2.y - p1.y;
    float z = p2.z - p1.z;
    return glm::vec3(x,y,z);
}

float computeDistance(glm::vec3 p1, glm::vec3 p2)
{
	float x = p2.x - p1.x;
    float y = p2.y - p1.y;
    float z = p2.z - p1.z;
	return sqrt(x*x + y*y + z*z);
}