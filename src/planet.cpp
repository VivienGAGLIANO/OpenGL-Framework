#include "planet.h"

Planet::Planet(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r)
	: CelestBody(name, v, p, glm::vec3(1.0f)), mass(m), radius(r), gradRotated(0.0f) 
{
	translate(p);
}

Planet::Planet(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r, const glm::vec3& scale)
	: CelestBody(name, v, p, scale), mass(m), radius(r), gradRotated(0.0f)
{
	translate(p);
}

void Planet::update(const double& delta_time)
{
	// This method gets called every frame
	// on inverse la rotation pour translate correctement sinon on se retrouve à faire n'importe quoi
	this->resetRotation();
	translate(this->position - this->prevPosition);
	this->makeRotation(delta_time*2);
	Object::update(delta_time); // call parent class update to handle graphic pipeline actions
}

void Planet::resetRotation()
{
	rotate(glm::vec3(0, 1, 0), glm::radians(-this->gradRotated));
}

void Planet::makeRotation(const double& delta_time)
{
	//rotate(glm::vec3(0, 1, 0), glm::radians(this->gradRotated) + glm::radians(90. * delta_time));
	this->gradRotated += delta_time * 90;
	rotate(glm::vec3(0, 1, 0), glm::radians(this->gradRotated));
}

float Planet::getMass() {
	return this->mass;
}

void Planet::addForce(glm::vec3 f)
{
	((CelestBody*)this)->addForce(f / this->mass);
}