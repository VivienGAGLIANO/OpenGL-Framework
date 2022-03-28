#include "scene.h"


Scene::Scene()
{
}

void Scene::update(const double& delta_time)
{
	for (auto object : objects)
	{
		object.update(delta_time);
	}
}

void Scene::render(Engine* engine)
{
	for (const auto & object : objects)
	{
		engine->render(camera, object);
	}
}
