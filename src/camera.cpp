#include "camera.h"

#include <glfw3.h>

Camera::Camera() : Object("Camera")
{
}

void Camera::update(const double& delta_time)
{
	
}

void Camera::process_keyboard(int key)
{
	glm::vec3 dir;
	switch (key)
	{
		case GLFW_KEY_W :
			dir = { 0, 0, -1 };
			break;

		case GLFW_KEY_S :
			dir = { 0, 0, 1 };
			break;

		case GLFW_KEY_D :
			dir = { 1, 0, 0 };
			break;

		case GLFW_KEY_A:
			dir = { -1, 0, 0 };
			break;

		default:
			dir = glm::vec3(0);
				break;
	}

	translate(dir);
}

glm::mat4 Camera::get_view() const
{
	return glm::inverse(model_matrix);
}
