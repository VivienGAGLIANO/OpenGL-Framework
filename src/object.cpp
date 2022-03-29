#include "object.h"

void Object::update(const double& delta_time)
{
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