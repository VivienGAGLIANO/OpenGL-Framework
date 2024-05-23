#include <fstream>
#include <iostream>

#include "performance.h"
#include "scene.h"


std::shared_ptr<Scene> Scene::active_scene;

Scene::Scene()
{
	// Perspective or orthogonal camera are available
	camera = std::make_shared<Camera>(PerspectiveCamera(glm::radians(60.f), float(1800) / float(1600), .1f, 1000.f));

	light = std::make_shared<Light>(Light
	{
	glm::vec3(0), // position

	glm::vec3(0.65f, 0.71f, 0.55f), // ambiant
	glm::vec3(0.91f, 0.84f, 0.57f), // diffuse
	glm::vec3(.4f),// specular

	15.f // shininess
	});

	populate();
}

void Scene::populate()
{
	auto planet = std::make_shared<Object>("Planet", glm::vec3(1.0));
	planet->set_material(std::make_shared<Material>());
	planet->set_model(std::make_shared<Model>("resources/model/cartoon/lowilds_planet/scene.gltf"));
	objects.push_back(planet);
}

Scene::~Scene() {}

std::shared_ptr<Camera> Scene::get_camera() const
{
	return camera;
}

std::shared_ptr<Light> Scene::get_light() const
{
	return light;
}

void Scene::render(Engine* engine)
{
	Performance::reset_vertex_count();
	Performance::reset_index_count();

	for (auto obj : objects)
	{
		obj->prepare_material();
		obj->render();
	}

	engine->render_skybox();
}

void Scene::update(const double& delta_time)
{
	camera->update(delta_time);

	for (auto obj : objects)
	{
		obj->update(delta_time);
	}
}
