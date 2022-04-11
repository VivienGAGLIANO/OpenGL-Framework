#ifndef CELESTBODY_H
#define CELESTBODY_H

#include "object.h"
#include <glm.hpp>

class CelestBody : public Object
{
	public:
		CelestBody(const std::string& name, const float m, const float r);
		virtual void update(const double& delta_time) override;
		virtual void resetRotation();
		virtual void makeRotation(const double& delta_time);
		virtual float getMass();
		
	protected:
		float mass;
		float radius;
		double gradRotated;

	private:

};

#endif
