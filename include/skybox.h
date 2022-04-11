#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <string>
#include <glm.hpp>
#include <vector>

#include "pipeline.h"


class Skybox
{
public:
	explicit Skybox(const std::string& path);
	void init();
	void render();

private:
	GLuint load_texture(const std::string& path);

	GLuint texture=0, vao, vbo;
    Pipeline pipeline;
};

inline std::vector<std::string> skybox_faces
{
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
};

inline std::vector<glm::vec3> skybox_vertices
{
	glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),

    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),

     glm::vec3(1.0f, -1.0f, -1.0f),
     glm::vec3(1.0f, -1.0f,  1.0f),
     glm::vec3(1.0f,  1.0f,  1.0f),
     glm::vec3(1.0f,  1.0f,  1.0f),
     glm::vec3(1.0f,  1.0f, -1.0f),
     glm::vec3(1.0f, -1.0f, -1.0f),

    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3( 1.0f,  1.0f,  1.0f),
    glm::vec3( 1.0f,  1.0f,  1.0f),
    glm::vec3( 1.0f, -1.0f,  1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),

    glm::vec3(-1.0f,  1.0f, -1.0f),
     glm::vec3(1.0f,  1.0f, -1.0f),
     glm::vec3(1.0f,  1.0f,  1.0f),
     glm::vec3(1.0f,  1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),

    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3( 1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3( 1.0f, -1.0f,  1.0f)
};
#endif