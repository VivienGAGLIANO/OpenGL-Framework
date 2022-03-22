#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>


class Renderer
{
public:
	Renderer();
	init();
	render(const Object& obj);

private:
	GLFWwindow *window;
};

#endif