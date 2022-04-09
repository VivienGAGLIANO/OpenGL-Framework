#include "planet.h"


Planet::Planet(const std::string& name, const float m, glm::vec3  a, glm::vec3  v, glm::vec3  p, const float r)
	: CelestBody(name, m, r), acceleration(a), velocity(v), position(p)
{
	translate(p);
}

void Planet::update(const double& delta_time)
{
	CelestBody::update(delta_time); // call parent class update to handle graphic pipeline actions
	glm::vec3 oldPos = this->position;

	// update the caracteristics of the planet
	
	this->velocity.x += this->acceleration.x * delta_time;
	this->velocity.y += this->acceleration.y * delta_time;
	this->velocity.z += this->acceleration.z * delta_time;

	this->position.x += this->velocity.x * delta_time;
	this->position.y += this->velocity.y * delta_time;
	this->position.z += this->velocity.z * delta_time;
	//glm::vec3 delta = this->position - oldPos;
	glm::vec3 delta(0.01f, 0.0f, 0.0f);

	// This method gets called every frame
	// on inverse la rotation pour translate correctement sinon on se retrouve à faire n'importe quoi
	this->resetRotation();
	translate(delta);
	this->makeRotation(delta_time);
}
