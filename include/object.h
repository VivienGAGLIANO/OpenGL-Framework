#ifndef OBJECT_H
#define OBJECT_H

#include <glm.hpp>

#include "material.h"
#include "model.h"


class Object
{
public:
	Object();
	void update(const double& delta_time);
	void prepare_material() const;
	void render();
	// long n_elements() const;

private:
	glm::mat4 model_matrix;
	Material material;
	Model model;
};

#endif