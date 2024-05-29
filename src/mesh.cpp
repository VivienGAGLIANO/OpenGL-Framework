#include <gtc/type_ptr.hpp>

#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures, const glm::vec3& mesh_color) :
	vertices(vertices), indices(indices), textures(textures), mesh_color(mesh_color)
{
	set_buffer_objects();
}

void Mesh::prepare_for_render(Pipeline pipeline)
{
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    unsigned int emissionNr = 0;
    unsigned int metallicNr = 0;
    unsigned int normalNr = 0;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(++diffuseNr);
        else if (name == "texture_specular")
            number = std::to_string(++specularNr);
        else if (name == "texture_emission")
            number = std::to_string(++emissionNr);
        else if (name == "texture_metallic")
            number = std::to_string(++metallicNr);
        else if (name == "texture_normal")
            number = std::to_string(++normalNr);

        pipeline.set_uniform_float(pipeline.get_fragment_id(), (name + number).c_str(), i);
        glBindTextureUnit(i, textures[i].id);
    }

    glBindVertexArray(vao);

    pipeline.set_uniform_vec3(pipeline.get_fragment_id(), "mesh_color", glm::value_ptr(mesh_color));
}

void Mesh::set_buffer_objects()
{
    glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    // Position
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
    glVertexArrayAttribBinding(vao, 0, 0);

    // Normal
    glEnableVertexArrayAttrib(vao, 2);
    glVertexArrayAttribFormat(vao, 2, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 2, vbo, offsetof(Vertex, normal), sizeof(Vertex));
    glVertexArrayAttribBinding(vao, 2, 2);

    // UV coord
    glEnableVertexArrayAttrib(vao, 3);
    glVertexArrayAttribFormat(vao, 3, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 3, vbo, offsetof(Vertex, uv), sizeof(Vertex));
    glVertexArrayAttribBinding(vao, 3, 3);

    glCreateBuffers(1, &ebo);
    glNamedBufferData(ebo, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
