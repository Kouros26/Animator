#pragma once

#include "Resources/resource.hpp"

#include <vector>

#include "texture.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 BiTangent;
};

class Mesh
{
public:

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

    void Draw(const unsigned shaderProgram) const;

private:

    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture> textures;

    unsigned VAO, VBO, EBO;

    void SetupMesh();
};