#include <gtc/type_ptr.hpp>
#include <iostream>

#include "scene.h"
#include "skybox.h"
#include "stb_image.h"


Skybox::Skybox(const std::string& path) :
    texture(load_cubemap_texture(path)),
    skybox_material(Material("resources/shader/skybox_vertex.glsl", "resources/shader/skybox_fragment.glsl", nullptr))
{
    glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, skybox_vertices.size() * sizeof(glm::vec3), glm::value_ptr(skybox_vertices.front()), GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(glm::vec3));

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    Sampler samp("Skybox sampler");
    glSamplerParameteri(samp.get_id(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(samp.get_id(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(samp.get_id(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(samp.get_id(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(samp.get_id(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    skybox_material.sampler = std::make_shared<Sampler>(samp);
}

void Skybox::render() const
{
    glDepthMask(GL_FALSE);
    skybox_material.prepare();

    auto cam = Scene::active_scene->get_camera();
    skybox_material.get_program().set_uniform_matrix("v", glm::value_ptr(glm::mat4(glm::mat3(cam->get_view()))));
    skybox_material.get_program().set_uniform_matrix("p", glm::value_ptr(cam->get_proj()));

    glBindVertexArray(vao);
    glBindTextureUnit(0, texture);
    glBindSampler(0, skybox_material.sampler->get_id());
    glDrawArrays(GL_TRIANGLES, 0, skybox_vertices.size());
    glDepthMask(GL_TRUE);
}

/// <summary>
/// Load cubemap texture data from file and create initialized Texture Object. If texture loading fails, no object is created and returned ID is invalid
/// </summary>
/// <param name="path">Path from project root to file directory</param>
/// <returns>Created Texture Object ID</returns>
GLuint Skybox::load_cubemap_texture(const std::string& path)
{
    auto cubemap_faces = /*cartoon ? cartoon_skybox_faces :*/ skybox_faces;

    GLuint textureID;

    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &textureID);
    
    int width, height, n_chan;
    unsigned char* data = stbi_load((path + cubemap_faces[0]).c_str(), &width, &height, &n_chan, 0);
    if (data)
    {
        glTextureStorage2D(textureID, 1, GL_RGB8, width, height);

        for (size_t face = 0; face < 6; ++face)
        {
            if (face != 0) data = stbi_load((path + cubemap_faces[face]).c_str(), &width, &height, &n_chan, 0);

            // face:
            // 0 = positive x face
            // 1 = negative x face
            // 2 = positive y face
            // 3 = negative y face
            // 4 = positive z face
            // 5 = negative z face

            if (data)
            {
                glTextureSubImage3D(
                    textureID,
                    0,
                    0,
                    0,
                    face,     // the offset to desired cubemap face, which offset goes to which face above
                    width,
                    height,
                    1,        // depth how many cubemap_faces to set, if this was 3 we'd set 3 cubemap cubemap_faces at once
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    data);
            }
            else
            {
                std::cerr << "Skybox face at " << path << cubemap_faces[face] << " couldn't be loaded." << std::endl;
                glDeleteTextures(1, &textureID);
            }

            stbi_image_free(data);
        }
    }
    else 
    {
        stbi_image_free(data); // needed ?
        std::cerr << "Skybox files at " << path << " couldn't be loaded." << std::endl;
        glDeleteTextures(1, &textureID);
    }

    return textureID;


    // Non-DSA texture

    //GLuint tex;
    //glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    //for (int i = 0; i < cubemap_faces.size(); ++i)
    //{
    //    int width, height, n_chan;
    //    unsigned char* data = stbi_load((path + cubemap_faces[i]).c_str(), &width, &height, &n_chan, 0);
    //    if (data)
    //    {
    //        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    }
    //    else
    //        std::cerr << "Skybox face " << path << cubemap_faces[i] << " couldn't be loaded.\n";

    //    stbi_image_free(data);
    //}

    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //return tex;
}
