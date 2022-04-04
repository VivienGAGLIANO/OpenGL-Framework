#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


class Camera : Object
{
public:
	Camera();
	virtual void update(const double& delta_time) override;
	void process_keyboard(int key, int action);
	glm::mat4 get_view() const;

private:
	void move_camera(const double& delta_time);

	glm::mat4 proj_matrix;
	bool should_move = false;
	bool move_forw = false, 
		 move_back = false, 
		 move_right = false, 
		 move_left = false, 
		 move_up = false, 
		 move_down = false;
	float camera_speed = .2f/*150.0f*/;


};

#endif