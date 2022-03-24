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
	void prepare_for_render() const;
	long n_elements() const;

private:
	glm::mat4 model_matrix;
	Material material;
	Model model;
};

#endif