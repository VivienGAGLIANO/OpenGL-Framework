#include "renderer.h"

#include <iostream>

Renderer::Renderer(const int width, const int height) : width(width), height(height)
{
}

void Renderer::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
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

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void Renderer::render(const Camera& camera, const Object& obj)
{
    //glBindVertexArray(obj.vao);
    //obj.use_pipeline();
    obj.prepare_for_render();

    glDrawElements(GL_TRIANGLES, obj.n_elements(), GL_UNSIGNED_INT, 0);
}

bool Renderer::should_render() const
{
    return !glfwWindowShouldClose(window);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // this->width = width;
    // this->height = height;
    glViewport(0, 0, width, height);
}