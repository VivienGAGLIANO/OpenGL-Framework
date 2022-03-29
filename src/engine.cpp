#include "engine.h"

#include <iostream>


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

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void Engine::render(const Camera& camera, const Object& obj)
{
    //glBindVertexArray(obj.vao);
    //obj.use_pipeline();
    obj.prepare_material();

    // obj.render();
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
}
