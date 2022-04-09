#ifndef PLANET_H
#define PLANET_H

#include "object.h"
#include "celestBody.h"
#include <glm.hpp>

class Planet : public CelestBody
{
	public:
		Planet(const std::string& name, const float m, glm::vec3 a, glm::vec3 v, glm::vec3 p, const float r);
		virtual void update(const double& delta_time) override;

	private:
		glm::vec3 force;
		glm::vec3 acceleration;
		glm::vec3 velocity;
		glm::vec3 position;
};

#endif