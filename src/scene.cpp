#include <fstream>
#include <iostream>

#include "performance.h"
#include "scene.h"


Scene* Scene::instance;

Scene::Scene()
{
	// Perspective or orthogonal camera are available
	camera = new PerspectiveCamera(glm::radians(60.f), float(1800) / float(1600), .1f, 1000.f);

	light = new Light
	{
		glm::vec3(0), // position

		glm::vec3(0.65f, 0.71f, 0.55f), // ambiant
		glm::vec3(0.91f, 0.84f, 0.57f), // diffuse
		glm::vec3(.4f),// specular

		15.f // shininess
	};

	populate();
}

void Scene::populate()
{
	auto planet = new Object("Planet", glm::vec3(1.0));
	planet->set_material(new Material);
	planet->set_model(new Model("resources/model/cartoon/lowilds_planet/scene.gltf"));
	objects.push_back(planet);
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

Light* Scene::get_light() const
{
	return light;
}

void Scene::update(const double& delta_time)
{
	camera->update(delta_time);

	for (auto obj : objects)
	{
		obj->prepare_material();
		obj->update(delta_time);
	}
}

void Scene::render(Engine* engine)
{
	Performance::reset_vertex_count();
	Performance::reset_index_count();

	for (Object *obj : objects)
	{
		obj->prepare_material();
		obj->render();
	}

	engine->render_skybox();
}

Scene* Scene::get_instance()
{
	if (!instance)
	{
		instance = new Scene();
	}
	return instance;
}
