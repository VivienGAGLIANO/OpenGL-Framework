#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


class Camera : Object
{
public:
	Camera();
	virtual void update(const double& delta_time) override;
	void process_keyboard(int key);
	glm::mat4 get_view() const;

private:
	glm::mat4 proj_matrix;


};

#endif