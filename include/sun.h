#ifndef SUN_H
#define SUN_H

#include "planet.h"


class Sun : public Planet
{
public:
	Sun(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r);
	Sun(const std::string& name, const float& m, const glm::vec3& v, const glm::vec3& p, const float& r, const glm::vec3& scale);
	virtual void update(const double& delta_time) override;
};


#endif