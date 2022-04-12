#include "planet.h"


Planet::Planet(const std::string& name, const float m, glm::vec3  v, glm::vec3  p, const float r)
	: Planet(name, m, v, p, r, glm::vec3(1.0f)) {}

Planet::Planet(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r,
	const glm::vec3& scale)
	: CelestBody(name, m, r, scale), velocity(v), position(p), force(glm::vec3(0.0f))
{
	translate(p);
}

void Planet::update(const double& delta_time)
{
	// This method gets called every frame
	// on inverse la rotation pour translate correctement sinon on se retrouve à faire n'importe quoi
	this->resetRotation();
	glm::vec3 delta = this->position - this->prevPosition;
	//if (this->name == "Planet_one")
	//	printf("\tdPos2 t+1 : (%f,%f,%f)\n", delta.x, delta.y, delta.z);

	translate(delta);
	this->makeRotation(delta_time);

	CelestBody::update(delta_time); // call parent class update to handle graphic pipeline actions
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
void Planet::resetForce(){
	this->force = glm::vec3(0.0f, 0.0f, 0.0f);
}
void Planet::addForce(glm::vec3 f) {
 	this->force.x += f.x / this->mass;
	this->force.y += f.y / this->mass;
	this->force.z += f.z / this->mass;
}
void Planet::setVelocity(const double& delta_time){
	this->velocity.x += this->force.x * delta_time;
	this->velocity.y += this->force.y * delta_time;
	this->velocity.z += this->force.z * delta_time;
}
void Planet::setPosition(const double& delta_time){
	this->prevPosition = this->position;
	this->position.x += this->velocity.x * delta_time;
	this->position.y += this->velocity.y * delta_time;
	this->position.z += this->velocity.z * delta_time;
}
