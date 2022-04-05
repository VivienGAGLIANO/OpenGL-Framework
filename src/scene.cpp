#include "scene.h"

#include "template.h"


Scene* Scene::instance;

Scene::Scene()
{
	populate_scene();
}

void Scene::populate_scene()
{
	// Perspective or orthogonal camera are available
	camera = new PerspectiveCamera(glm::radians(60.f), float(800) / float(600), .1f, 100.f);

	// Scene objects
	auto backpack = new Template("backpack");
	backpack->set_material(new Material);
	backpack->set_model(new Model("resources/model/backpack/backpack.obj"));
	objects.push_back(backpack);

	auto suzanne = new Template("suzanne");
	suzanne->set_material(new Material);
	suzanne->set_model(new Model("resources/model/suzenne.obj"));
	suzanne->translate(glm::vec3(1.5, 0, 0));
	objects.push_back(suzanne);
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
