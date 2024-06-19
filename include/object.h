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

	std::shared_ptr<Material> get_material() const;
	void set_material(std::shared_ptr<Material> mat);
	std::shared_ptr<Model> get_model() const;
	void set_model(std::shared_ptr<Model> model);
	
	void prepare_material() const;
	virtual void update(const double& delta_time);
	
	void translate(const glm::vec3& v);
	void rotate(const glm::vec3& axis, const float& angle);
	void set_scale(const glm::vec3& factor);

	std::string name;

protected:
	glm::vec3 scale;
	glm::mat4 model_matrix;
	std::shared_ptr<Material> material;
	std::shared_ptr<Model> model;
};

#endif