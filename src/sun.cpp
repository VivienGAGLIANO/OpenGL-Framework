#include "sun.h"


Sun::Sun(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p) :
	Sun(name, m, v, p, glm::vec3(1.0)) {}

Sun::Sun(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale) :
	Planet(name, m, v, p, scale) {}

void Sun::update(const double& delta_time)
{
	Planet::update(delta_time);

	Scene::get_instance()->get_light()->set_position(position);
}
