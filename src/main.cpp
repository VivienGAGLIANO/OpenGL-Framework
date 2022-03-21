#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "data.h"
#include "pipeline.h"
#include "texture.h"


constexpr int width = 800;
constexpr int height = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

glm::mat4 view(1.0f);
glm::mat4 projection(1.0f);
// position
glm::vec3 position = glm::vec3(0, 0, 5);
// horizontal angle : toward -Z
float horizontalAngle = glm::pi<float>();
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 60.0f;

float speed = 50.0f; // 3 units / second
float mouseSpeed = 5.f;

void control_camera(GLFWwindow *window, float delta_time)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, (double)width / 2.0, (double)height / 2.0);

    horizontalAngle += mouseSpeed * delta_time * ((float)width / 2.0f - xpos);
    verticalAngle += mouseSpeed * delta_time * ((float)height / 2.0f - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );
    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );
    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * delta_time * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * delta_time * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * delta_time * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * delta_time * speed;
    }


    // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projection = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    view = glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
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
    glEnable(GL_CULL_FACE);

    return window;
}

int main()
{
    // Init
	GLFWwindow* window = init_engine();
    if (window == nullptr)
        return -1;


    // Setting up object buffers
    GLuint vao, vbo, cbo, ibo, uvbo;

	glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

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

    glCreateBuffers(1, &uvbo);
    glNamedBufferData(uvbo, uv_coords.size() * sizeof(glm::vec2), &uv_coords.front(), GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 2);
    glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 2, uvbo, 0, sizeof(glm::vec2));
    glVertexArrayAttribBinding(vao, 2, 2);

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, indices.size() * sizeof(glm::uvec3), &(indices.front()), GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    // Graphic pipeline
    Pipeline pipeline = Pipeline("resources/vertex.glsl", "resources/fragment.glsl");


    // Texture
    Texture texture("resources/uvtemplate.bmp");


    // Transformation matrices
    glm::mat4 model = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(2, 1, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    projection = glm::perspective(glm::radians(60.f), float(width) / float(height), .1f, 100.f);


    auto time = glfwGetTime();

	while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        control_camera(window, glfwGetTime() - time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::rotate(glm::mat4(1.0f), 2 * glm::pi<float>() * (float)glfwGetTime() / 10.f, glm::vec3(0, 1, 0));
        pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "m", glm::value_ptr(model));
	    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "v", glm::value_ptr(view));
	    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "p", glm::value_ptr(projection));

        glBindVertexArray(vao);
        pipeline.use_pipeline();

        glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);

        time = glfwGetTime();
        glfwSwapBuffers(window);
    }

    
    glfwTerminate();
    return 0;
}