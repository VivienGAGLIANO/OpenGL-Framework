#include "scene.h"
#include "planet.h"
#include "interpolation.h"
#include "Utils.h"
#include <stdio.h>
using namespace std;

#include <iostream>
#include <fstream>

Scene* Scene::instance;
float G = 1;//0.66741;
bool print = false;

// pour l'iterpolation
const long t_cycle = 10000; // le temps d'un cycle d'animation (en millisecondes)
double t = 0;

ofstream myfile1, myfile2, myfile3, myfile4, myfile5;

Scene::Scene()
{
	myfile1.open("log/orbit1.txt");
	myfile2.open("log/orbit2.txt");
	myfile3.open("log/orbit3.txt");
	myfile4.open("log/orbit4.txt");
	myfile5.open("log/orbit5.txt");
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
	// horse->set_scale(glm::vec3(.3, .3, .3));
	// objects.push_back(horse);

	// auto suzanne = new Template("suzanne");
	// suzanne->set_material(new Material);
	// suzanne->set_model(new Model("resources/model/suzanne.obj"));
	// suzanne->translate(glm::vec3(3, 0, 0));
	// objects.push_back(suzanne);

	//auto ref = new CelestBody("reference", 1, 1.f);
	//ref->set_material(new Material);
	//ref->set_model(new Model("resources/model/planet/scene.gltf"));
	//ref->translate(glm::vec3(2, 0, -2));
	//ref->set_scale(glm::vec3(.2, .2, .2));
	//objects.push_back(ref);
	//nbObjects++;
	auto vessel = new Interpolation("Spaceship", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.02f));
	vessel->translate(glm::vec3(0.0f, 10.0f, 0.0f)); // comme la position n'est pas encore update elle se retrouve tjr en 0 0 0
	vessel->set_material(new Material);
	vessel->set_model(new Model("resources/model/soucoupe/soucoupe.gltf"));
	objects.push_back(vessel);
	nbObjects++;

	auto sun = new Planet("Sun", 100000, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.05f));
	sun->set_material(new Material);
	sun->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(sun);
	
	auto planet1 = new Planet("Planet_one", 1, glm::vec3(0.0f, 0.0f, 71.0f), glm::vec3(20.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.01f));
	planet1->set_material(new Material);
	planet1->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(planet1);

	auto planet2 = new Planet("Planet_two", 1, glm::vec3(0.0f, 0.0f, 58.0f), glm::vec3(30.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.005f));
	planet2->set_material(new Material);
	planet2->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(planet2);

	auto planet3 = new Planet("Planet_three", 1, glm::vec3(0.0f, 0.0f, 44.8f), glm::vec3(50.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.008f));
	planet3->set_material(new Material);
	planet3->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(planet3);

	auto planet4 = new Planet("Planet_four", 100, glm::vec3(0.0f, 0.0f, 31.61f), glm::vec3(100.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.02f));
	planet4->set_material(new Material);
	planet4->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(planet4);

	auto planet5 = new Planet("Planet_five", 0.001, glm::vec3(0.0f, 0.0f, 33.992264f), glm::vec3(107.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.008f));
	planet5->set_material(new Material);
	planet5->set_model(new Model("resources/model/planet/scene.gltf"));
	objects.push_back(planet5);
	
}

Scene::~Scene()
{
	myfile1.close();
	myfile2.close();
	myfile3.close();
	myfile4.close();
	myfile5.close();
	delete camera;
	for (Object* obj : objects)
		delete obj;
}

Camera* Scene::get_camera() const
{
	return camera;
}

void Scene::resetForces()
{
	for (Object* obj : objects)
	{
		if (dynamic_cast<Planet*>(obj))
		{
			((Planet*)obj)->resetForce();
		}
	}
}

glm::vec3 attraction(Planet* o1, Planet* o2)
{
	// calculate the gravitational force between object object and object2
	float dist = glm::length(o2->getPosition() - o1->getPosition());

	if (dist <= 1) // pour �viter l'explosion du systeme
		return glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 forceDir = glm::normalize(o2->getPosition() - o1->getPosition()); // direction
	float M1M2 = o1->getMass() * o2->getMass();
	float forceMag = (G * M1M2) / (dist * dist);
	glm::vec3 forceVec = forceDir * forceMag;
	if (o1->name == "Sun")
		if (o2->name == "Planet_one")
			myfile1 << dist << "\n";
		else if (o2->name == "Planet_two")
			myfile2 << dist << "\n";
		else if (o2->name == "Planet_three")
			myfile3 << dist << "\n";
		else if (o2->name == "Planet_four")
			myfile4 << dist << "\n";
	
	if (o1->name == "Planet_four")
			myfile5 << dist << "\n";

	if (print && o2->name == "Planet_five") {
		cout << o2->name.c_str() <<  " ----{ " << dist << " }---> " << o1->name.c_str() << " : \t Force : " << forceMag << "\n";
		cout << "\tDirection:\t(" << forceDir.x << ", " << forceDir.y << ", " << forceDir.z << ")\n";
		cout << "\tVecteur force:\t(" << forceVec.x << ", " << forceVec.y << "," << forceVec.z << ")\n";
		cout << "\t" << o1->name.c_str() << "\t(" << ((Planet*)o1)->getPosition().x << ", " << ((Planet*)o1)->getPosition().y << ", " << ((Planet*)o1)->getPosition().z << ")\n";
		cout << "\t" << o2->name.c_str() << "\t(" << ((Planet*)o2)->getPosition().x << ", " << ((Planet*)o2)->getPosition().y << ", " << ((Planet*)o2)->getPosition().z << ")\n";
	}
	return forceVec;
}

// It is said on the web that actualise the velocity and the position not at the same time increase the stability of the system
// https://youtu.be/7axImc1sxa0?t=84
void Scene::updateVelocity(const double& delta_time)
{
	if (print)
		cout << "-------------------------------------------------------\n";
	for (int i = 0; i < objects.size(); i++)
	{
		Object* object = objects[i];
		if (dynamic_cast<Planet*>(object))
		{
			// update the gravitational forces for every object i in the scene
			for (int j = i + 1; j < objects.size(); j++)
			{
				Object* object2 = objects[j];
				glm::vec3 force = attraction((Planet*)object, (Planet*)object2);
				((Planet*)object)->addForce(force);
				((Planet*)object2)->addForce(-force);
			}
			((Planet*)object)->setVelocity(delta_time);
		}
	}
}

void Scene::updatePosition(const double& delta_time)
{
	for (int i = 0; i < objects.size(); i++)
	{
		Object* object = objects[i];
		if (dynamic_cast<Planet*>(object))
		{
			((Planet*)object)->setPosition(delta_time);
		}
		else if (dynamic_cast<Interpolation*>(object))
		{
			// les /4 sont pour accélérer le mouvement de la soucoupe par 4, sinon c'est trop lent
			// en fait 4 fois moins de points donc on va plus vite vu que le temps est normalisé entre 2 pts
			if (t >= 1 * (int(((Interpolation*)object)->getNbPoints()/4)))
				t = 0.0;

			glm::vec3 pos = ((Interpolation*)object)->cat_rom_t(t/(int(((Interpolation*)object)->getNbPoints()/4)));// / double(t_cycle));
			((Interpolation*)object)->setPosition(pos);
		}
		object->update(delta_time);
	}
}

void Scene::update(const double& delta_time)
{
	t += delta_time;
	camera->update(delta_time);

	resetForces();
	updateVelocity(delta_time);
	updatePosition(delta_time);
}

void Scene::render(Engine* engine)
{
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
