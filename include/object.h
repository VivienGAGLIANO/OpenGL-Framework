#ifndef OBJECT_H
#define OBJECT_H

#include <glm.hpp>

#include "material.h"
#include "model.h"


class Object
{
public:
	Object(const std::string &name, Material mat, Model model);
	virtual void update(const double& delta_time);
	void prepare_material() const;
	void render();
	// long n_elements() const;

	std::string name;

private:
	glm::mat4 model_matrix;
	Material material;
	Model model;
};

#endif