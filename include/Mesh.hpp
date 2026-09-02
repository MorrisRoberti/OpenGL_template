#pragma once
#include <GL/glew.h>
#include <vector>
#include "./Vertex.hpp"

class Mesh
{
public:
    Mesh() = default;

    bool init(const std::vector<Vertex> &vertices,
              const std::vector<unsigned int> &indices)
    {

        numIndices = indices.size();

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(Vertex) * vertices.size(),
                     &vertices.at(0),
                     GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(unsigned int) * numIndices,
                     &indices.at(0),
                     GL_STATIC_DRAW);
        return true;
    }

    GLuint VBO;
    GLuint EBO;
    unsigned int numIndices;
    unsigned int materialIndex;
};