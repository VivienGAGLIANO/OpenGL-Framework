#include <glm/ext.hpp>
#include <iostream>
#include <thread>

#include "application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "performance.h"


bool Application::ui_active = true;

Application::Application()
{
	std::cout << "Starting application\n\n";

    initialize_gl();

	engine = std::make_unique<Engine>();
	scene = std::make_shared<Scene>();
	Scene::active_scene = scene;
	Performance::initialize();
}

Application::~Application()
{
	Performance::deinitialize();
}

/// <summary>
/// Main application loop
/// </summary>
void Application::start()
{
	ImGuiIO& io = ImGui::GetIO();
	
	while (should_render())
	{
		glfwPollEvents();

		// Initialize and draw UI
		engine->draw_ui(ui_active); // TODO try to remove ui_active from the inside of draw_ui method

		// Reset buffers and window
		glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update scene
		scene->update(io.DeltaTime);

		// Render scene
		engine->render(*scene);

		// Render UI
		engine->render_ui();

		glfwSwapBuffers(window);
	}


	terminate();
}

/// <summary>
/// <para>
/// Initialize OpenGL context
/// </para>
/// <para>
/// Create OpenGL window, set various user input and debug callbacks, initialize ImGui context
/// </para>
/// </summary>
void Application::initialize_gl()
{
	// TODO move OpenGL init stuff in here, not in engine class. Be careful to handle scene and engine initialization after basic GL stuff
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GFLW window.\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD.\n";
        return;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    /*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);*/

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    // Set up debug output
    auto message_callback = [](
        GLenum src,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* user_param)
    {
        auto const src_str = [src]() {
            switch (src)
            {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            }
        }();

        auto const type_str = [type]() {
            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR: return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER: return "MARKER";
            case GL_DEBUG_TYPE_PUSH_GROUP: return "PUSH_GROUP";
            case GL_DEBUG_TYPE_POP_GROUP: return "POP_GROUP";
            case GL_DEBUG_TYPE_OTHER: return "OTHER";
            }
        }();

        auto const severity_str = [severity]() {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            }
        }();

        std::cout << src_str << " " << type_str << " (" << severity_str << ") " << id << ": " << message << '\n';
    };

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // fire messages synchronously to guarantee function call order
    glDebugMessageCallback(message_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE); // filter debug callback messages
}

/// <summary>
/// Terminates OpenGL context and window
/// </summary>
void Application::terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwDestroyWindow(window); // normally not needed as glfwTerminate() automatically destroys remaining windows

	// TODO clear objects buffers

	glfwTerminate();
}

void Application::update_camera(Camera& camera)
{
}

/// <summary>
/// Check if current window should be closed
/// </summary>
bool Application::should_render() const
{
    return !glfwWindowShouldClose(window);
}

/// <summary>
/// Callback for window size change
/// </summary>
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/// <summary>
/// Callback for keyboard input
/// </summary>
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        ui_active = !ui_active;

    std::vector move = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL };
    if (std::find(move.cbegin(), move.cend(), key) != move.cend())
    {
        Scene::active_scene->get_camera()->process_keyboard(key, action);
    }
}

/// <summary>
/// Callback for mouse input
/// </summary>
void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Scene::active_scene->get_camera()->process_mouse(xpos, ypos);
}

