#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../include/Shape.hpp"

class Cube : public Shape
{

public:
    Cube(float size, const Texture *texture) : Shape(36, 24)
    {
        genVertices(size);
        genTextureVertices();
        genIndices();

        setBuffers();
    }

    Cube(float size, glm::vec3 color) : Shape(36, 24)
    {
        genVertices(size);
        genIndices();
        genColors(color);

        setBuffers();
    }

private:
    void genVertices(float size)
    {
        float half = size / 2.0f;

        vertices = {
            // front
            -half, half, half,  // Top-Left
            half, half, half,   // Top-Right
            -half, -half, half, // Bottom-Left
            half, -half, half,  // Bottom-Right

            // back
            half, half, -half,   // Top-Left
            -half, half, -half,  // Top-Right
            half, -half, -half,  // Bottom-Left
            -half, -half, -half, // Bottom-Right

            // left
            -half, half, -half,  // Top-Left
            -half, half, half,   // Top-Right
            -half, -half, -half, // Bottom-Left
            -half, -half, half,  // Bottom-Right

            // right
            half, half, half,   // Top-Left
            half, half, -half,  // Top-Right
            half, -half, half,  // Bottom-Left
            half, -half, -half, // Bottom-Right

            // top
            -half, half, -half, // Top-Left
            half, half, -half,  // Top-Right
            -half, half, half,  // Bottom-Left
            half, half, half,   // Bottom-Right

            // bottom
            -half, -half, half,  // Top-Left
            half, -half, half,   // Top-Right
            -half, -half, -half, // Bottom-Left
            half, -half, -half   // Bottom-Right
        };
    }

    void genIndices()
    {
        indices.clear();
        indices.reserve(36);

        for (unsigned int i = 0; i < 6; ++i)
        {
            unsigned int offset = i * 4;

            indices.push_back(offset + 0);
            indices.push_back(offset + 2);
            indices.push_back(offset + 3);

            indices.push_back(offset + 0);
            indices.push_back(offset + 3);
            indices.push_back(offset + 1);
        }
    }

    void genColors(glm::vec3 color)
    {
        colors.clear();
        colors.reserve(72);

        for (int i = 0; i < 24; ++i)
        {
            colors.push_back(color.x);
            colors.push_back(color.y);
            colors.push_back(color.z);
        }
    }

    void genTextureVertices()
    {
        texCoords.clear();
        texCoords.reserve(48);

        for (int i = 0; i < 6; ++i)
        {
            texCoords.push_back(0.0f);
            texCoords.push_back(1.0f); // Top-Left
            texCoords.push_back(1.0f);
            texCoords.push_back(1.0f); // Top-Right
            texCoords.push_back(0.0f);
            texCoords.push_back(0.0f); // Bottom-Left
            texCoords.push_back(1.0f);
            texCoords.push_back(0.0f); // Bottom-Right
        }
    }
};