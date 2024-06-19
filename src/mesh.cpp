#include <gtc/type_ptr.hpp>

#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures, const glm::vec3& mesh_color) :
	vertices(vertices), indices(indices), textures(textures), mesh_color(mesh_color)
{
	set_buffer_objects();
}

/// <summary>
/// Prepare mesh for draw call. Binds texture units, samplers, vao and sets mesh color
/// </summary>
/// <param name="material">Material to use for rendering. Uniforms are set for the programs of given material</param>
/// <returns>Number of indices in mesh</returns>
int Mesh::prepare_for_render(const Material& material) const
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

        //pipeline.set_uniform_unsigned_int(pipeline.get_fragment_id(), (name + number).c_str(), i); // no need for this as texture bindings are declared in shader
        
        glBindSampler(i, material.sampler->get_id());
        glBindTextureUnit(i, textures[i].id);
    }

    glBindVertexArray(vao);

    material.get_program().set_uniform_vec3("mesh_color", glm::value_ptr(mesh_color));

    return indices.size();
}

/// <summary>
/// Create vertex array object with 3 attributes, position normal and uv, packed in the same buffer
/// </summary>
void Mesh::set_buffer_objects()
{
    glCreateVertexArrays(1, &vao);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
    glVertexArrayElementBuffer(vao, ibo);
    
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glEnableVertexArrayAttrib(vao, 2);
    
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
    
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
    glVertexArrayVertexBuffer(vao, 1, vbo, offsetof(Vertex, normal), sizeof(Vertex));
    glVertexArrayVertexBuffer(vao, 2, vbo, offsetof(Vertex, uv), sizeof(Vertex));
    
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 1);
    glVertexArrayAttribBinding(vao, 2, 2);

    
    // Binding vbo only once to vao is slower for an unknown reason.
    // TODO figure this out, and which approach is more efficient
    //glCreateBuffers(1, &vbo);
    //glNamedBufferData(vbo, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    //glCreateBuffers(1, &ibo);
    //glNamedBufferData(ibo, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

    //glCreateVertexArrays(1, &vao);

    //glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
    //glVertexArrayElementBuffer(vao, ibo);

    //glEnableVertexArrayAttrib(vao, 0);
    //glEnableVertexArrayAttrib(vao, 1);
    //glEnableVertexArrayAttrib(vao, 2);

    //glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    //glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    //glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));

    //glVertexArrayAttribBinding(vao, 0, 0);
    //glVertexArrayAttribBinding(vao, 1, 0);
    //glVertexArrayAttribBinding(vao, 2, 0);
}
