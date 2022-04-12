#include "celestBody.h"

CelestBody::CelestBody(const std::string& name, const float m, const float r)
	: Object(name), mass(m), radius(r), gradRotated(0.0f)
{
}

void CelestBody::update(const double& delta_time)
{
	Object::update(delta_time); // call parent class update to handle graphic pipeline actions
}

void CelestBody::resetRotation()
{
	rotate(glm::vec3(0, 1, 0), glm::radians(-this->gradRotated));
}

void CelestBody::makeRotation(const double& delta_time)
{
	//rotate(glm::vec3(0, 1, 0), glm::radians(this->gradRotated) + glm::radians(90. * delta_time));
	this->gradRotated += delta_time * 90;
	rotate(glm::vec3(0, 1, 0), glm::radians(this->gradRotated));
}

float CelestBody::getMass(){
	return this->mass;
}