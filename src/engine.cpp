#include <gtc/type_ptr.hpp>
#include <iostream>

#include "engine.h"
#include "stb_image.h"


Engine::Engine(const int width, const int height) : width(width), height(height)
{
}

void Engine::init()
{
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    skybox = new Skybox("resources/skybox/");
    skybox->init();
}

void Engine::render_skybox()
{
    skybox->render();
}

bool Engine::should_render() const
{
    return !glfwWindowShouldClose(window);
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // this->width = width;
    // this->height = height;
    glViewport(0, 0, width, height);
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    std::vector move = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL };
    if (std::find(move.cbegin(), move.cend(), key) != move.cend())
        Scene::get_instance()->get_camera()->process_keyboard(key, action);
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Scene::get_instance()->get_camera()->process_mouse(xpos, ypos);
}

