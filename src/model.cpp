#include "model.h"

long Model::n_elements() const
{
	return 3 * indices.size();
}

void Model::prepare() const
{
	glBindVertexArray(vao);
}

void Model::set_buffer_objects()
{

}
