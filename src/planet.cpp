#include "planet.h"


Planet::Planet(const std::string& name, const int m, glm::vec3  v, glm::vec3  p, const float r)
	: CelestBody(name, m, r), velocity(v), position(p), force(glm::vec3(0.0f))
{
	translate(p);
}

void Planet::update(const double& delta_time)
{
	CelestBody::update(delta_time); // call parent class update to handle graphic pipeline actions
	glm::vec3 oldPos = this->position;

	// update the caracteristics of the planet	
	this->velocity.x += this->force.x * delta_time;
	this->velocity.y += this->force.y * delta_time;
	this->velocity.z += this->force.z * delta_time;

	this->position.x += this->velocity.x/this->mass * delta_time;
	this->position.y += this->velocity.y/this->mass * delta_time;
	this->position.z += this->velocity.z/this->mass * delta_time;
	
	glm::vec3 delta = this->position - oldPos;

	// This method gets called every frame
	// on inverse la rotation pour translate correctement sinon on se retrouve à faire n'importe quoi
	this->resetRotation();
	translate(delta);
	this->makeRotation(delta_time);
}

// every getter and setter for force, acceleration, velocity and position
glm::vec3 Planet::getForce(){
	return this->force;
}
glm::vec3 Planet::getVelocity(){
	return this->velocity;
}
glm::vec3 Planet::getPosition(){
	return this->position;
}

void Planet::setForce(glm::vec3 f) {
	this->force.x += f.x;
	this->force.y += f.y;
	this->force.z += f.z;
}
void Planet::setVelocity(glm::vec3 v){
	this->velocity = v;
}
void Planet::setPosition(glm::vec3 p){
	this->position = p;
}
