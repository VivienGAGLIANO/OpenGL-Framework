#include "template.h"


Template::Template(const std::string& name) :
	Object(name), // call parent class constructor
	attribute(1.2)
{
	// Initialize object here
}

void Template::update(const double& delta_time)
{
	Object::update(delta_time); // call parent class update to handle graphic pipeline actions

	// This method gets called every frame
	rotate(glm::vec3(0, 1, 0), glm::radians(90. * delta_time * attribute));
}
