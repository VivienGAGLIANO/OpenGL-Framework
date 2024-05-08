#include "application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/ext.hpp>
#include <iostream>
#include <thread>
#include <windows.h>


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
	std::cout << "Starting application\n\n";


	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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
		scene->render(engine);

		// Render UI
		engine->render_ui();

		glfwSwapBuffers(engine->window);
	}


	terminate();
}

void Application::init()
{
	// TODO move OpenGL init stuff in here, not in engine class
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
