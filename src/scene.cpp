#include "scene.h"


Scene::Scene()
{
	// objects.push_back()
	Material mat = Material();
	Model model("resources/model/suzanne.obj");
	objects.emplace_back(new Object("backpack", mat, model));
}

void Scene::update(const double& delta_time)
{
	for (auto object : objects)
	{
		object->update(delta_time);
	}
}

void Scene::render(Engine* engine)
{
	for (Object *obj : objects)
	{
		obj->prepare_material();

		obj->render();
		// engine->render(camera, object);
	}
}
