#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>

#include "object.h"
#include "scene.h"


struct Camera;


class Engine
{
public:
	Engine(const int width = 800, const int height = 600);
	void init();
	void render(const Camera& camera, const Object& obj);
	bool should_render() const;

	int width, height;
	GLFWwindow *window;

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif