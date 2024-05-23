#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <glm.hpp>
#include <string>
#include <vector>

#include "pipeline.h"


class Skybox
{
public:
	explicit Skybox(const std::string& path);
	void render();

private:
	GLuint load_texture(const std::string& path);

	GLuint texture=0, vao, vbo;
    Pipeline pipeline;
};

inline std::vector<std::string> cartoon_skybox_faces
{
	"right_d.jpg",
    "left_d.jpg",
    "top_d.jpg",
    "bottom_d.jpg",
    "front_d.jpg",
    "back_d.jpg"
};

inline std::vector<std::string> skybox_faces
{
	"right_milk.jpg",
	"left_milk.jpg",
	"top_milk.jpg",
	"bottom_milk.jpg",
	"front_milk.jpg",
	"back_milk.jpg"
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