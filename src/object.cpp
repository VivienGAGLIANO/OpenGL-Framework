#include "object.h"

#include <glfw3.h>
#include <iostream>
#include <glm/ext.hpp>

#include "scene.h"


Object::Object(const std::string &name) : name(name), model_matrix(glm::mat4(1.0)) {}

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
	// THIS IS TEST AND SHOULD BE RE-ORGANIZED WITH CAMERA CLASS
	glm::mat4 mod = glm::mat4(1.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(2, 1, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 view = Scene::get_instance()->get_camera()->get_view();
	glm::mat4 projection = glm::perspective(glm::radians(60.f), float(800) / float(600), .1f, 100.f);

	auto pip = material->get_pipeline();

	mod = glm::rotate(glm::mat4(1.0f), 2 * glm::pi<float>() * (float)glfwGetTime() / 10.f, glm::vec3(0, 1, 0));

	pip.set_uniform_matrix(pip.get_vertex_id(), "m", glm::value_ptr(mod));
	pip.set_uniform_matrix(pip.get_vertex_id(), "v", glm::value_ptr(view));
	pip.set_uniform_matrix(pip.get_vertex_id(), "p", glm::value_ptr(projection));
}

void Object::prepare_material() const
{
	material->prepare();
}

void Object::render()
{
	prepare_material();

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

//long Object::n_elements() const
//{
//	// return model.n_elements();
//	return 0;
//}