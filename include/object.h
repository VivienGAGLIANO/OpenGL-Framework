#ifndef OBJECT_H
#define OBJECT_H

#include <glm.hpp>

#include "material.h"
#include "model.h"


class Object
{
public:
	Object(const std::string &name, const glm::vec3& scale);
	Object(const std::string& name);
	virtual ~Object();
	void set_material(Material* mat);
	void set_model(Model* model);
	virtual void update(const double& delta_time);
	void prepare_material() const;
	void render();
	void translate(const glm::vec3& v);
	void rotate(const glm::vec3& axis, const float& angle);
	void scale(const glm::vec3& factor);

	std::string name;

protected:
	glm::mat4 model_matrix;
	Material *material = nullptr;
	Model *model = nullptr;
};

#endif