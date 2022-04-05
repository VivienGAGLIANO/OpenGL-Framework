#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


class Camera : public Object
{
public:
	void update(const double& delta_time) override;
	void process_keyboard(int key, int action);
	glm::mat4 get_view() const;
	glm::mat4 get_proj() const;

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
	float camera_speed = 25.0f;

protected:
	explicit Camera(const glm::mat4& proj);

};


class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const float& fov, const float& aspect, const float& near, const float& far);
};


class OrthogonalCamera : public Camera
{
public:
	OrthogonalCamera(const float& xmin, const float& xmax, const float& ymin, const float& ymax);
};

#endif