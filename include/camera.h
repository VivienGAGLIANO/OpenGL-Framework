#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


class Camera : public Object
{
public:
	void update(const double& delta_time) override;
	void process_keyboard(int key, int action);
	void process_mouse(double xpos, double ypos);
	glm::vec3 get_position() const;
	glm::mat4 get_view() const;
	glm::mat4 get_proj() const;

private:
	void move_camera(const double& delta_time);
	void rotate_camera(const double& delta_time);

	glm::mat4 proj_matrix;
	bool should_move = false, should_rotate = false;
	bool move_forw = false, 
		 move_back = false, 
		 move_right = false, 
		 move_left = false, 
		 move_up = false, 
		 move_down = false;
	float camera_speed = 25.0f;
	glm::vec3 position = glm::vec3(0,0,0), 
			  front = glm::vec3(0,0,-1), 
			  up = glm::vec3(0,1,0), 
			  right = glm::vec3(1,0,0);
	double o_xpos, o_ypos;
	float pitch = 0, yaw = -90;
	float sensitivity = .5f;
	bool first_frame = true;

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