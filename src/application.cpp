#include "application.h"

#include <iostream>


Application::Application() : engine(new Renderer), scene(new Scene)
{
	engine->init();
}

void Application::start()
{
	std::cout << "Starting application\n";

	double time = glfwGetTime();
	while (engine->should_render())
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
