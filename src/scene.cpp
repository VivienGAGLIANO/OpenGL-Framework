#include "scene.h"
#include "planet.h"
#include "Utils.h"
#include <stdio.h>
using namespace std;


Scene* Scene::instance;
int nbObjects = 0;
double G = 0.0066741;

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

	auto ref = new CelestBody("reference", 1, 1.f);
	ref->set_material(new Material);
	ref->set_model(new Model("resources/model/planet/scene.gltf"));
	ref->scale(glm::vec3(.2, .2, .2));
	objects.push_back(ref);
	nbObjects++;

	auto ref2 = new CelestBody("reference2", 1, 1.f);
	ref2->set_material(new Material);
	ref2->translate(glm::vec3(2.5, 0, 0));
	ref2->set_model(new Model("resources/model/planet/scene.gltf"));
	ref2->scale(glm::vec3(.1, .1, .1));
	objects.push_back(ref2);
	nbObjects++;

	auto sun = new Planet("Sun", 1000, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.f);
	sun->set_material(new Material);
	sun->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(sun);
	nbObjects++;
	
	auto planet1 = new Planet("Planet_one", 1, glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 1.f);
	planet1->set_material(new Material);
	planet1->set_model(new Model("resources/model/planet/scene.gltf"));
	planet1->scale(glm::vec3(.2, .2, .2));
	objects.push_back(planet1);
	nbObjects++;
	
	//auto planet2= new Planet("Planet_two", 1, glm::vec3(0, 0, 0), glm::vec3(10, 0, 0), glm::vec3(0, 0, -5), 1.f);
	//planet2->set_material(new Material);
	//planet2->set_model(new Model("resources/model/planet/scene.gltf"));
	//planet2->scale(glm::vec3(.3, .3, .3));
	//objects.push_back(planet2);
	//nbObjects++;
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

void resetForces(std::vector<Object*> objects)
{
	for (Object* obj : objects)
	{
		if (dynamic_cast<Planet*>(obj))
		{
			((Planet*)obj)->setForce(glm::vec3(0, 0, 0));
		}
	}
}

glm::vec3 attraction(Planet* o1, Planet* o2)
{
	// appliying force on object2
	// calculate the gravitational force between object object and object2
	glm::vec3 r_vec = o1->getPosition() - o2->getPosition(); // difference
	double r_mag = magnitude(r_vec); // distance
	glm::vec3 r_hat = operator_divide(r_vec, r_mag); // direction
	float M1M2 = o1->getMass() * o2->getMass();

 	float force_mag = (double)(G * M1M2) / (r_mag * r_mag);
	glm::vec3 force_vec = -force_mag * r_hat;

	if (o1->name == "Sun") {
		printf("-------------------------------------------------------\n");
		printf("%s --> %s : \t Force: %f\n", o2->name.c_str(), o1->name.c_str(), force_mag);
		printf("\tDirection: (%f,%f,%f)", r_hat.x, r_hat.y, r_hat.z);
		printf("\tDistance: %f\n", r_mag);
		printf("\tposition: (%f,%f,%f)\n", ((Planet*)o1)->getPosition().x, ((Planet*)o1)->getPosition().y, ((Planet*)o1)->getPosition().z);
		printf("\tposition: (%f,%f,%f)\n", ((Planet*)o2)->getPosition().x, ((Planet*)o2)->getPosition().y, ((Planet*)o2)->getPosition().z);
	}

	return force_vec;
}

void Scene::update(const double& delta_time)
{
	camera->update(delta_time);

	resetForces(objects);

	//printf("\n");
	for (int i=0; i < nbObjects; i++)
	{
		Object* object = objects[i];
		if (dynamic_cast<Planet*>(object))
		{
			// update the gravitational forces for every object i in the scene
			for (int j=i+1; j < nbObjects; j++)
			{
				Object* object2 = objects[j];
				glm::vec3 force = attraction((Planet*)object, (Planet*)object2);
				((Planet*)object)->setForce(force);
				((Planet*)object2)->setForce(-force);					
			}
		}
		//printf("%s: old position=(%f,%f,%f) --> ",object->name.c_str(),((Planet*)object)->getPosition().x, ((Planet*)object)->getPosition().y, ((Planet*)object)->getPosition().z);
		object->update(delta_time);
		//printf("new position=(%f,%f,%f)\n",((Planet*)object)->getPosition().x, ((Planet*)object)->getPosition().y, ((Planet*)object)->getPosition().z);	
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
