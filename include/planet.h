#ifndef PLANET_H
#define PLANET_H

#include "object.h"
#include "celestBody.h"
#include "Utils.h"
#include <glm.hpp>

class Planet : public CelestBody
{
	public:
		Planet(const std::string& name, const int m, glm::vec3 a, glm::vec3 v, glm::vec3 p, const float r);
		virtual void update(const double& delta_time) override;
		virtual float computeDistance(const glm::vec3& p);

		glm::vec3 getForce();
		glm::vec3 getAcceleration();
		glm::vec3 getVelocity();
		glm::vec3 getPosition();
		void apply_force(double force, glm::vec3 dir);
		void setAcceleration(glm::vec3 a);
		void setVelocity(glm::vec3 v);
		void setPosition(glm::vec3 p);

	private:
		glm::vec3 force;
		glm::vec3 acceleration;
		glm::vec3 velocity;
		glm::vec3 position;
};

#endif