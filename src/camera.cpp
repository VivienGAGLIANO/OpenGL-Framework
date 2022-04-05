#include "camera.h"

#include <glfw3.h>
#include <iostream>
#include <ext.hpp>

/*********************************** Camera ***********************************/

Camera::Camera(const glm::mat4& proj) : Object("Camera"), proj_matrix(proj) {}

void Camera::update(const double& delta_time)
{
	if (should_move)
		move_camera(delta_time);

	if (should_rotate)
		rotate_camera(delta_time);
}

void Camera::process_keyboard(int key, int action)
{
	const bool press = action == GLFW_PRESS || action == GLFW_REPEAT;
	switch (key)
	{
		case GLFW_KEY_W :
			move_forw = press;
			break;

		case GLFW_KEY_S :
			move_back = press;
			break;

		case GLFW_KEY_D :
			move_right = press;
			break;

		case GLFW_KEY_A:
			move_left = press;
			break;

		case GLFW_KEY_SPACE:
			move_up = press;
			break;

		case GLFW_KEY_LEFT_CONTROL:
			move_down = press;
			break;

		default:
			break;

	}

	should_move = move_forw || move_back || move_right || move_left || move_up || move_down;
}

void Camera::process_mouse(double xpos, double ypos)
{
	if (first_frame)
	{
		o_xpos = xpos;
		o_ypos = ypos;
		first_frame = false;
	}

	double x_off = sensitivity * (xpos - o_xpos),
		   y_off = sensitivity * (o_ypos - ypos);
	o_xpos = xpos;
	o_ypos = ypos;

	pitch = glm::clamp(pitch + y_off, -89.0, 89.0);
	yaw += x_off;

	should_rotate = true;
}

glm::mat4 Camera::get_view() const
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::get_proj() const
{
	return proj_matrix;
}

void Camera::move_camera(const double& delta_time)
{
	float speed = camera_speed * (float)delta_time;

	glm::vec3 dir(0);
	if (move_forw)
		dir += glm::vec3(0,0,-1);

	if (move_back)
		dir += glm::vec3(0,0,1);

	if (move_right)
		dir += glm::vec3(1,0,0);

	if (move_left)
		dir += glm::vec3(-1,0,0);

	if (move_up)
		dir += glm::vec3(0,1,0);

	if (move_down)
		dir += glm::vec3(0,-1,0);

	position += speed * dir;
}

void Camera::rotate_camera(const double& delta_time)
{
	auto r_pitch = glm::radians(pitch),
		 r_yaw = glm::radians(yaw);

	front = glm::normalize(glm::vec3(cos(r_pitch) * cos(r_yaw), 
									   sin(r_pitch), 
									   cos(r_pitch) * sin(r_yaw)));

	right = glm::normalize(glm::cross(up, front));
	// up = glm::cross(front, right);

	should_rotate = false;
}


/*********************************** Perspective Camera ***********************************/

PerspectiveCamera::PerspectiveCamera(const float& fov, const float& aspect, const float& near, const float& far) :
	Camera(glm::perspective(fov, aspect, near, far)) {}


/*********************************** Orthogonal Camera ***********************************/

OrthogonalCamera::OrthogonalCamera(const float& xmin, const float& xmax, const float& ymin, const float& ymax) :
	Camera::Camera(glm::ortho(xmin, xmax, ymin, ymax)) {}