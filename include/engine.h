#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>

#include "object.h"
#include "scene.h"


class Engine
{
public:
	Engine(const int width = 800, const int height = 600);
	void init();
	void render_skybox();
	bool should_render() const;

	int width, height;
	GLFWwindow *window;

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	GLuint load_skybox(const std::string& path);

	GLuint skybox;
};

inline std::vector<std::string> skybox_faces
{
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
};

#endif