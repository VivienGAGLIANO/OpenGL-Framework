#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>

#include "skybox.h"


class Engine
{
public:
	Engine(const int width = 800, const int height = 600);
	~Engine();
	void init();
	void render_skybox();
	bool should_render() const;
	void to_render_target();

	int width, height;
	GLFWwindow *window;

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	GLuint init_framebuffer();

	GLuint fbo;
	Skybox* skybox;
};

#endif