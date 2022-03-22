#ifndef OBJECT_H
#define OBJECT_H

#include <glm.hpp>

#include "material.h"
#include "model.h"


class Object
{
public:
	Object();

private:
	glm::mat4 model_matrix;
	Material material;
	Model model;
};

#endif