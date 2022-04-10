#include "Utils.h"

glm::vec3 x_double(glm::vec3 vector, double d)
{
    double X = vector.x * d;
    double Y = vector.y * d;
    double Z = vector.z * d;
    return glm::vec3(X,Y,Z);
}