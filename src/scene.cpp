#include "scene.h"


Scene::Scene()
{
	// objects.push_back()
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
	for (auto & obj : objects)
	{
		obj.prepare_material();

		obj.render();
		// engine->render(camera, object);
	}
}
