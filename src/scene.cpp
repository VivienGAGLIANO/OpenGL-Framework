#include "scene.h"
#include "planet.h"
#include "Utils.h"
#include <stdio.h>


Scene* Scene::instance;
int nbObjects = 0;

Scene::Scene()
{
	populate();
}

void Scene::populate()
{
	// Perspective or orthogonal camera are available
	camera = new PerspectiveCamera(glm::radians(60.f), float(800) / float(600), .1f, 100.f);

	// Scene objects
	// auto backpack = new Template("backpack");
	// backpack->set_material(new Material);
	// backpack->set_model(new Model("resources/model/backpack/backpack.obj"));
	// objects.push_back(backpack);

	// auto horse = new Template("horse");
	// horse->set_material(new Material);
	// horse->set_model(new Model("resources/model/rocking-horse-with-wheels/source/Rocking_horse_with_wheels_SF/Rocking_horse_with_wheels_SF.obj"));
	// horse->translate(glm::vec3(-3, 0, 0));
	// horse->scale(glm::vec3(.3, .3, .3));
	// objects.push_back(horse);

	// auto suzanne = new Template("suzanne");
	// suzanne->set_material(new Material);
	// suzanne->set_model(new Model("resources/model/suzanne.obj"));
	// suzanne->translate(glm::vec3(3, 0, 0));
	// objects.push_back(suzanne);

	auto sun = new Planet("Sun", 1000, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.f);
	sun->set_material(new Material);
	sun->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(sun);
	nbObjects++;
	
	auto planet1 = new Planet("Planet_one", 10, glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), glm::vec3(0, 0, -5), 1.f);
	planet1->set_material(new Material);
	planet1->set_model(new Model("resources/model/planet/scene.gltf"));
	planet1->scale(glm::vec3(.4, .4, .4));
	objects.push_back(planet1);
	nbObjects++;
	
	auto planet2= new Planet("Planet_two", 1, glm::vec3(0, 0, 0), glm::vec3(0, 0, -8), glm::vec3(8, 0, 0), 1.f);
	planet2->set_material(new Material);
	planet2->set_model(new Model("resources/model/planet/scene.gltf"));
	planet2->scale(glm::vec3(.5, .5, .5));
	objects.push_back(planet2);
	nbObjects++;
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
	printf("\n");
	for (int i=0; i < nbObjects; i++)
	{
		Object* object = objects[i];
		if (dynamic_cast<Planet*>(object))
		{
			// update the gravitational forces for every object i in the scene
			for (int j=i+1; j < nbObjects; j++)
			{
				Object* object2 = objects[j];
				// appliying force on object2
				// calculate the gravitational force between object object and object2
				float distance = ((Planet*)object)->computeDistance(((Planet*)object2)->getPosition());
				float masses = ((Planet*)object)->getMass() * ((Planet*)object2)->getMass();
				double force = masses / (distance*distance);
				force *= ((CelestBody*)object)->G;
				// compute the direction of the force
				glm::vec3 direction = glm::normalize(((Planet*)object2)->getPosition() - ((Planet*)object)->getPosition());
				((Planet*)object)->apply_force(force, direction);
				((Planet*)object2)->apply_force(force, -direction);

			}
			printf("%s: old position=(%f,%f,%f) --> ",object->name.c_str(),((Planet*)object)->getPosition().x, ((Planet*)object)->getPosition().y, ((Planet*)object)->getPosition().z);
			object->update(delta_time);
			printf("new position=(%f,%f,%f)\n",((Planet*)object)->getPosition().x, ((Planet*)object)->getPosition().y, ((Planet*)object)->getPosition().z);
			
		}
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
