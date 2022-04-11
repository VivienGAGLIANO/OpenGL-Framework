#ifndef PLANET_H
#define PLANET_H

#include "object.h"
#include "celestBody.h"
#include "Utils.h"
#include <glm.hpp>

class Planet : public CelestBody
{
	public:
		Planet(const std::string& name, const int m, glm::vec3 v, glm::vec3 p, const float r);
		virtual void update(const double& delta_time) override;

		glm::vec3 getForce();
		glm::vec3 getVelocity();
		glm::vec3 getPosition();
		void resetForce();
		void setForce(glm::vec3 f);
		void setVelocity(const double& delta_time);
		void setPosition(const double& delta_time);

	private:
		glm::vec3 force;
		glm::vec3 velocity;
		glm::vec3 position;
		glm::vec3 prevPosition;
};

#endif