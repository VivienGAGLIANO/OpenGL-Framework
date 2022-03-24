#include "object.h"

void Object::prepare_for_render() const
{
	model.prepare();
	material.prepare();
}

long Object::n_elements() const
{
	return model.n_elements();
}