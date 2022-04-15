#include <fstream>
#include <iostream>

#include "interpolation.h"
#include "planet.h"
#include "scene.h"
#include "sun.h"

Scene* Scene::instance;

float G = 1; // constante de gravitation
// pour l'interpolation
const long t_cycle = 10000; // le temps d'un cycle d'animation (en millisecondes)
double t = 0;

std::ofstream myfile1, myfile2, myfile3, myfile4, myfile5;

Scene::Scene()
{
	myfile1.open("log/orbit1.txt");
	myfile2.open("log/orbit2.txt");
	myfile3.open("log/orbit3.txt");
	myfile4.open("log/orbit4.txt");
	myfile5.open("log/orbit5.txt");

	// Perspective or orthogonal camera are available
	camera = new PerspectiveCamera(glm::radians(60.f), float(1800) / float(1600), .1f, 100.f);

	light = new Light
	{
		glm::vec3(0.78f, 0.71f, 0.48f), // ambiant

		glm::vec3(0.65f, 0.71f, 0.55f), // diffuse
		glm::vec3(0.91f, 0.84f, 0.57f), // specular
		glm::vec3(.5f),

		15.f
	};

	if (cartoon)
		populateCartoon();
	else
		populate();
}

void Scene::populate()
{
	auto vessel = new Interpolation("Spaceship", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.02f));
	vessel->set_material(new Material);
	vessel->set_model(new Model("resources/model/realiste/soucoupe/soucoupe.gltf"));
	objects.push_back(vessel); 

	
	auto sun = new Sun("Sun", 100000, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.f, glm::vec3(1.0f));
	sun->set_material(new Material);
	sun->set_model(new Model("resources/model/realiste/sun/scene.gltf"));
	objects.push_back(sun);
	

	auto planet1 = new Planet("Planet_one", 1, glm::vec3(0.0f, 0.0f, -71.0f), glm::vec3(-20.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.05f));
	planet1->set_material(new Material("resources/shader/vertex.glsl", "resources/shader/fragment_rocket_moon.glsl"));
	planet1->set_model(new Model("resources/model/realiste/venus/scene.gltf"));
	objects.push_back(planet1);

	
	auto planet2 = new Planet("Planet_two", 1, glm::vec3(0.0f, 0.0f, 58.0f), glm::vec3(30.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.03f));
	planet2->set_material(new Material);
	planet2->set_model(new Model("resources/model/realiste/coruscant/scene.gltf"));
	objects.push_back(planet2);
	 
	auto planet3 = new Planet("Planet_three", 1, glm::vec3(0.0f, 0.0f, 44.75f), glm::vec3(50.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.04f));
	planet3->set_material(new Material("resources/shader/vertex.glsl", "resources/shader/fragment_horizon.glsl"));
	planet3->set_model(new Model("resources/model/realiste/rocket_orbiting_moon/scene.gltf"));
	objects.push_back(planet3);
	 
	auto planet4 = new Planet("Planet_four", 100, glm::vec3(0.0f, 0.0f, -31.61f), glm::vec3(-80.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.05f));
	planet4->set_material(new Material);
	planet4->set_model(new Model("resources/model/realiste/saturn/scene.gltf"));
	objects.push_back(planet4);
	 
	auto planet5 = new Planet("Planet_five", 1, glm::vec3(0.0f, 0.0f, -35.0f), glm::vec3(-50.0f, 20.0f, 0.0f), 1.f, glm::vec3(4.0f));
	planet5->set_material(new Material("resources/shader/vertex.glsl", "resources/shader/fragment_coruscant.glsl"));
	planet5->set_model(new Model("resources/model/realiste/horizon_world/scene.gltf"));
	objects.push_back(planet5);
	
}

void Scene::populateCartoon()
{
	G = 10;

	
	auto p0 = new Planet("p0", 10000, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.2f));
	p0->set_material(new Material("resources/shader/vertex.glsl", "resources/shader/fragment_bear.glsl"));
	p0->set_model(new Model("resources/model/cartoon/bear_planet/scene.gltf"));
	objects.push_back(p0);

	auto p1 = new Sun("p1", 1, glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(10.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.2f));
	p1->set_material(new Material("resources/shader/vertex.glsl", "resources/shader/fragment_lowpoly_sun.glsl"));
	p1->set_model(new Model("resources/model/cartoon/sun_lowpoly/scene.gltf"));
	objects.push_back(p1);

	auto p2 = new Planet("p2", 10, glm::vec3(0.0f, 0.0f, -70.0f), glm::vec3(-10.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.2f));
	p2->set_material(new Material);
	p2->set_model(new Model("resources/model/cartoon/lowilds_planet/scene.gltf"));
	objects.push_back(p2);

	auto p3 = new Planet("p3", 10, glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(15.0f, 0.0f, 0.0f), 1.f, glm::vec3(0.4f));
	p3->set_material(new Material);
	p3->set_model(new Model("resources/model/cartoon/penguin_planet/scene.gltf"));
	objects.push_back(p3);

	auto p4 = new Planet("p4", 10, glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f), 1.f, glm::vec3(0.6f));
	p4->set_material(new Material);
	p4->set_model(new Model("resources/model/cartoon/clutter/scene.gltf"));
	objects.push_back(p4);
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

Light* Scene::get_light() const
{
	return light;
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
		else
			myfile5 << dist << "\n";
	
	return forceVec;
}

// It is said on the web that actualise the velocity and the position not at the same time increase the stability of the system
// https://youtu.be/7axImc1sxa0?t=84
void Scene::updateVelocity(const double& delta_time)
{
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
