#include "scene.h"


Scene* Scene::instance;

Scene::Scene() : camera(new Camera)
{
	auto backpack = new Object("backpack");
	backpack->set_material(new Material);
	backpack->set_model(new Model("resources/model/backpack/backpack.obj"));
	objects.push_back(backpack);
}

Scene::~Scene()
{
	delete camera;
	for (Object* obj : objects)
		delete obj;
}

Camera* Scene::get_camera() const
{
	return camera;
}

void Scene::update(const double& delta_time)
{
	camera->update(delta_time);

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

Scene* Scene::get_instance()
{
	if (!instance)
	{
		instance = new Scene();
	}
	return instance;
}
