#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "object.h"


class Template : public Object
{
public:
	Template(const std::string& name);
	virtual void update(const double& delta_time) override;



private:
	float attribute;
	
};

#endif