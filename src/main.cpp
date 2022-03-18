#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "data.h"
#include "pipeline.h"


constexpr int width = 800;
constexpr int height = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* init_engine()
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
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD.\n";
        return nullptr;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return window;
}

int main()
{
    // Init
	GLFWwindow* window = init_engine();
    if (window == nullptr)
        return -1;


    // Setting up object buffers
    GLuint vao, vbo, cbo, ibo;

	glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, vertices.size() * sizeof(glm::vec3), &(vertices.front()), GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec3));
    glVertexArrayAttribBinding(vao, 0, 0);

    glCreateBuffers(1, &cbo);
    glNamedBufferData(cbo, colors.size() * sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 1, cbo, 0, sizeof(glm::vec3));
    glVertexArrayAttribBinding(vao, 1, 1);

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, indices.size() * sizeof(glm::uvec3), &(indices.front()), GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    // Graphic pipeline
    Pipeline pipeline = Pipeline("resources/vertex.glsl", "resources/fragment.glsl");


    // Transformation matrices
    glm::mat4 model = glm::mat4(1.0f),
              view = glm::lookAt(glm::vec3(2, 1, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)),
              projection = glm::perspective(glm::radians(60.f), float(width) / float(height), .1f, 100.f);

    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "m", glm::value_ptr(model));
    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "v", glm::value_ptr(view));
    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "p", glm::value_ptr(projection));


	while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::rotate(glm::mat4(1.0f), 2 * glm::pi<float>() * (float)glfwGetTime() / 10.f, glm::vec3(0, 1, 0));
        pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "m", glm::value_ptr(model));

        glBindVertexArray(vao);
        pipeline.use_pipeline();

        glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    
    glfwTerminate();
    return 0;
}