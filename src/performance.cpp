#include "performance.h"


Performance* Performance::instance;

Performance::Performance()
{
}

Performance::~Performance()
{
}

void Performance::initialize()
{
	instance = new Performance();
}

void Performance::deinitialize()
{
	delete instance;
}

unsigned int Performance::get_vertex_count()
{
	return instance->vertex_count;
}

void Performance::increment_vertex_count(unsigned int count)
{
	instance->vertex_count += count;
}

void Performance::reset_vertex_count()
{
	instance->vertex_count = 0;
}

unsigned int Performance::get_index_count()
{
	return instance->index_count;
}

void Performance::increment_index_count(unsigned int count)
{
	instance->index_count += count;
}

void Performance::reset_index_count()
{
	instance->index_count = 0;
}