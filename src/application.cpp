#include <glm/ext.hpp>
#include <iostream>
#include <thread>

#include "application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "performance.h"


Application::Application()
{
	std::cout << "Starting application\n\n";

	engine = std::make_unique<Engine>();
	scene = std::make_shared<Scene>();
	Scene::active_scene = scene;
	Performance::initialize();
}

Application::~Application()
{
	Performance::deinitialize();
}

void Application::start()
{
	ImGuiIO& io = ImGui::GetIO();

	while (engine->should_render())
	{
		glfwPollEvents();

		// Initialize and draw UI
		engine->draw_ui();

		// Reset buffers and window
		glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update scene
		scene->update(io.DeltaTime);

		// Render scene
		engine->render(*scene);

		// Render UI
		engine->render_ui();

		glfwSwapBuffers(engine->window);
	}


	terminate();
}

void Application::initialize()
{
	// TODO move OpenGL init stuff in here, not in engine class. Be careful to handle scene and engine initialization after basic GL stuff
}

void Application::terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// TODO clear objects buffers

	glfwTerminate();
}

void Application::update_camera(Camera& camera)
{
}
