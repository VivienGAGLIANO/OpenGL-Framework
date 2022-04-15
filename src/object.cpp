#include "object.h"

#include <glfw3.h>
#include <iostream>
#include <glm/ext.hpp>

#include "scene.h"


Object::Object(const std::string& name, const glm::vec3& scale) : name(name), model_matrix(glm::mat4(1.0f))
{
	this->set_scale(scale);
}

Object::Object(const std::string &name) : Object(name, glm::vec3(1.0)) {}

Object::~Object()
{
	delete material;
	delete model;
}

void Object::set_material(Material* mat)
{
	this->material = mat;
}

void Object::set_model(Model* model)
{
	this->model = model;
}

void Object::update(const double& delta_time)
{
	// Pass MVP matrices to shader
	auto pip = material->get_pipeline();

	pip.set_uniform_matrix(pip.get_vertex_id(), "m", glm::value_ptr(glm::scale(model_matrix, scale)));
	pip.set_uniform_matrix(pip.get_vertex_id(), "v", glm::value_ptr(Scene::get_instance()->get_camera()->get_view()));
 	pip.set_uniform_matrix(pip.get_vertex_id(), "p", glm::value_ptr(Scene::get_instance()->get_camera()->get_proj()));

	pip.set_uniform_light(pip.get_fragment_id(), *Scene::get_instance()->get_light());
	pip.set_uniform_vec3(pip.get_fragment_id(), "cam_pos", glm::value_ptr(Scene::get_instance()->get_camera()->get_position()));
}

void Object::prepare_material() const
{
	material->prepare();
}

void Object::render()
{
	for (auto mesh : model->get_meshes())
	{
		mesh.prepare_for_render(material->get_pipeline());

		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void Object::translate(const glm::vec3& t)
{
	model_matrix = glm::translate(model_matrix, t);
}

void Object::rotate(const glm::vec3& axis, const float& angle)
{
	model_matrix = glm::rotate(model_matrix, angle, axis);
}

void Object::set_scale(const glm::vec3& factor)
{
	this->scale = factor;  // glm::scale(model_matrix, factor);
}

//long Object::n_elements() const
//{
//	// return model.n_elements();
//	return 0;
//}