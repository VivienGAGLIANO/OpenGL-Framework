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

glm::vec3 normalize(glm::vec3 v)
{
    float a, b, c;
    if (v.x >= 0)
        a = v.x;
    else
        a = -v.x;
    if (v.y >= 0)
        b = v.y;
    else
        b = -v.y;
    if (v.z >= 0)
        c = v.z;
    else
        c = -v.z;

    float total = a+b+c;
    float x = v.x / total;
    float y = v.y / total;
    float z = v.z / total;
    return glm::vec3(x,y,z);
}

float magnitude(glm::vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float computeDistance(glm::vec3 p1, glm::vec3 p2)
{
	float x = p2.x - p1.x;
    float y = p2.y - p1.y;
    float z = p2.z - p1.z;
	return sqrt(x*x + y*y + z*z);
}