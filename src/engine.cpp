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
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    skybox = load_skybox("resources/skybox/");
}

void Engine::render_skybox()
{

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

GLuint Engine::load_skybox(const std::string& path)
{
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    int width, height, n_chan;
    for (int i = 0; i < skybox_faces.size(); ++i)
    {
        unsigned char* data = stbi_load((path + skybox_faces[i]).c_str(), &width, &height, &n_chan, 0);
        if (data)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            std::cerr << "Skybox face " << path << skybox_faces[i] << " couldn't be loaded.\n";

    	stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return tex;
}
