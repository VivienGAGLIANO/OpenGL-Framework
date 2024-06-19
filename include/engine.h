#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>

#include "object.h"
#include "scene.h"
#include "skybox.h"


class Engine
{
public:
	~Engine();
	Engine(const int width = 800, const int height = 600);
	void render_skybox() const;

	void render(const Scene& scene) const;
	bool should_render() const;

	void draw_ui();
	void render_ui();
	bool should_render_ui() const;

	int width, height;
	GLFWwindow *window;

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	std::unique_ptr<Skybox> skybox;
	static bool ui_active;
};

#endif