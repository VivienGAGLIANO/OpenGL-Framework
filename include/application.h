#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "engine.h"
#include "scene.h"


class Application
{
public:
	Application();
	~Application();
	void start();

	int width=800, height=600;
	GLFWwindow* window;

private:
	void initialize_gl();
	void terminate();

	void update_camera(Camera &camera);
	bool should_render() const;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	std::unique_ptr<Engine> engine;
	std::shared_ptr<Scene> scene;
	static bool ui_active;
};

#endif