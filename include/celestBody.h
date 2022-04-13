#ifndef CELESTBODY_H
#define CELESTBODY_H

#include "object.h"
#include <glm.hpp>

class CelestBody : public Object
{
	public:
		CelestBody(const std::string& name, const glm::vec3& v, const glm::vec3& p);
		CelestBody(const std::string& name, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale);
		virtual void update(const double& delta_time) override;

		glm::vec3 getForce();
		glm::vec3 getVelocity();
		glm::vec3 getPosition();
		void resetForce();
		void addForce(glm::vec3 f);
		void setVelocity(const double& delta_time);
		void setPosition(const double& delta_time);

private:
	glm::vec3 force;
	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 prevPosition;

};

#endif
