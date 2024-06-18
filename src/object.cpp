#include <glfw3.h>
#include <glm/ext.hpp>
#include <iostream>

#include "object.h"
#include "performance.h"
#include "scene.h"


Object::Object(const std::string& name, const glm::vec3& scale) : name(name), model_matrix(glm::mat4(1.0f))
{
	this->set_scale(scale);
}

Object::Object(const std::string &name) : Object(name, glm::vec3(1.0)) {}

Object::~Object() {}

void Object::set_material(std::shared_ptr<Material> mat)
{
	this->material = mat;
}

void Object::set_model(std::shared_ptr<Model> model)
{
	this->model = model;
}

void Object::update(const double& delta_time)
{
	// Pass MVP matrices to shader
	auto program = material->get_program();

	program.set_uniform_matrix("m", glm::value_ptr(glm::scale(model_matrix, scale)));
	program.set_uniform_matrix("v", glm::value_ptr(Scene::active_scene->get_camera()->get_view()));
 	program.set_uniform_matrix("p", glm::value_ptr(Scene::active_scene->get_camera()->get_proj()));

	program.set_uniform_light(*Scene::active_scene->get_light());
	program.set_uniform_vec3("cam_pos", glm::value_ptr(Scene::active_scene->get_camera()->get_position()));
}

void Object::prepare_material() const
{
	material->prepare();
}

void Object::render()
{
	// Render object
	for (auto mesh : model->get_meshes())
	{
		mesh.prepare_for_render(*material.get());

		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);

		Performance::increment_index_count(mesh.indices.size());
		Performance::increment_vertex_count(mesh.vertices.size());
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
	this->scale = factor;
}