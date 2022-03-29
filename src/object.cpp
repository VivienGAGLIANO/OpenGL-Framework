#include "object.h"

#include <iostream>

Object::Object(const std::string &name, Material mat, Model model) : name(name), model_matrix(glm::mat4(1.0)), material(mat), model(model) {}

void Object::update(const double& delta_time)
{
	// Pass MVP matrices to shader
}

void Object::prepare_material() const
{
	// model.prepare();
	material.prepare();
}

void Object::render()
{
	prepare_material();

	for (auto mesh : model.get_meshes())
	{
		mesh.prepare_for_render(material.get_pipeline());

		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	}
}

//long Object::n_elements() const
//{
//	// return model.n_elements();
//	return 0;
//}