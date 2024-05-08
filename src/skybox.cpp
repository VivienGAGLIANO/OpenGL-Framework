#include <gtc/type_ptr.hpp>
#include <iostream>

#include "scene.h"
#include "skybox.h"
#include "stb_image.h"


Skybox::Skybox(const std::string& path) : texture(load_texture(path)), pipeline("resources/shader/skybox_vertex.glsl", "resources/shader/skybox_fragment.glsl") {}

void Skybox::init()
{
    glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, skybox_vertices.size() * sizeof(glm::vec3), glm::value_ptr(skybox_vertices.front()), GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec3));
    glVertexArrayAttribBinding(vao, 0, 0);
}

void Skybox::render()
{
    glDepthMask(GL_FALSE);
    pipeline.use_pipeline();

    auto cam = Scene::get_instance()->get_camera();
    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "v", glm::value_ptr(glm::mat4(glm::mat3(cam->get_view()))));
    pipeline.set_uniform_matrix(pipeline.get_vertex_id(), "p", glm::value_ptr(cam->get_proj()));

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLES, 0, skybox_vertices.size());
    glDepthMask(GL_TRUE);
}

GLuint Skybox::load_texture(const std::string& path)
{
    auto faces = /*cartoon ? cartoon_skybox_faces :*/ skybox_faces;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    int width, height, n_chan;
    for (int i = 0; i < faces.size(); ++i)
    {
        unsigned char* data = stbi_load((path + faces[i]).c_str(), &width, &height, &n_chan, 0);
        if (data)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            std::cerr << "Skybox face " << path << faces[i] << " couldn't be loaded.\n";

        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return tex;
}
