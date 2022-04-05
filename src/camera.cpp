#include "camera.h"

#include <glfw3.h>
#include <iostream>

Camera::Camera() : Object("Camera")
{
}

void Camera::update(const double& delta_time)
{
	if (should_move)
		move_camera(delta_time);
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

glm::mat4 Camera::get_view() const
{
	return glm::inverse(model_matrix);
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

	translate(speed * dir);
}
