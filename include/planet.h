#ifndef PLANET_H
#define PLANET_H

#include "object.h"
#include "celestBody.h"
#include "Utils.h"
#include <glm.hpp>

class Planet : public CelestBody
{
	public:
		Planet(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r);
		Planet(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r, const glm::vec3& scale);
		virtual void update(const double& delta_time) override;

		virtual void resetRotation();
		virtual void makeRotation(const double& delta_time);
		virtual float getMass();
		void addForce(glm::vec3 f);

	protected:
		float mass;
		float radius;
		double gradRotated;
};

#endif