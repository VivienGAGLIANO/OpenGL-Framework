#ifndef OBJECT_H
#define OBJECT_H

#include <glm.hpp>

#include "material.h"
#include "model.h"


class Object
{
public:
	Object(const std::string &name);
	void set_material(Material* mat);
	void set_model(Model* model);
	virtual void update(const double& delta_time);
	void prepare_material() const;
	void render();
	// long n_elements() const;

	std::string name;

protected:
	glm::mat4 model_matrix;
	Material *material = nullptr;
	Model *model = nullptr;
};

#endif