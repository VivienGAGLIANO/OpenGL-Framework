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

    Material get_material() const;

    int prepare_for_render() const;
    void restore() const;

private:
	GLuint load_cubemap_texture(const std::string& path);

	GLuint texture, vao, vbo;
    Material skybox_material;
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
	"test_right_milk.jpg",
	"test_left_milk.jpg",
	"test_top_milk.jpg",
	"test_bottom_milk.jpg",
	"test_front_milk.jpg",
	"test_back_milk.jpg"
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