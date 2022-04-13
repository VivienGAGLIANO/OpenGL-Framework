#include "celestBody.h"

CelestBody::CelestBody(const std::string& name, const glm::vec3& v, const glm::vec3& p)
	: CelestBody(name, v, p, glm::vec3(0.0f)) {}

CelestBody::CelestBody(const std::string& name, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale)
	: Object(name, scale), velocity(v), position(p), force(glm::vec3(0.0f)) {}

void CelestBody::update(const double& delta_time)
{
	translate(this->position - this->prevPosition);
	Object::update(delta_time); // call parent class update to handle graphic pipeline actions
}

// every getter and setter for force, acceleration, velocity and position
glm::vec3 CelestBody::getForce() {
	return this->force;
}
glm::vec3 CelestBody::getVelocity() {
	return this->velocity;
}
glm::vec3 CelestBody::getPosition() {
	return this->position;
}
void CelestBody::resetForce() {
	this->force = glm::vec3(0.0f, 0.0f, 0.0f);
}
void CelestBody::addForce(glm::vec3 f) {
	this->force.x += f.x;
	this->force.y += f.y;
	this->force.z += f.z;
}
void CelestBody::setVelocity(const double& delta_time) {
	this->velocity.x += this->force.x * delta_time;
	this->velocity.y += this->force.y * delta_time;
	this->velocity.z += this->force.z * delta_time;
}
void CelestBody::setPosition(const double& delta_time) {
	this->prevPosition = this->position;
	this->position.x += this->velocity.x * delta_time;
	this->position.y += this->velocity.y * delta_time;
	this->position.z += this->velocity.z * delta_time;
}