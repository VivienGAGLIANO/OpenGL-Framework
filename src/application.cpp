#include "application.h"

#include <iostream>


Application::Application()
{
	engine = new Engine();
	engine->init();
	scene = Scene::get_instance();
}

Application::~Application()
{
	delete engine;
	delete scene;
}

void Application::start()
{
	std::cout << "Starting application\n";

	double time = glfwGetTime();
	while (engine->should_render()) // TODO move this to engine class perhaps ?
	{
		glfwPollEvents();
		// camera control
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->update(glfwGetTime() - time);
		scene->render(engine);

		time = glfwGetTime();
		glfwSwapBuffers(engine->window);
	}

	terminate();
}

void Application::init()
{
}

void Application::terminate()
{
}

void Application::update_camera(Camera& camera)
{
}
