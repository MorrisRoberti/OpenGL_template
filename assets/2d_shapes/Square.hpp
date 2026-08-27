#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../../include/Shape.hpp"

class Square : public Shape
{

public:
    Square() = default;

    Square(float size, const Texture *texture) : Shape(6, 4)
    {
        genVertices(size);
        genTextureVertices(size);
        genIndices();

        setBuffers();
    }

    Square(float size, glm::vec3 color) : Shape(6, 4)
    {
        genVertices(size);
        genIndices();
        genColors(color);

        setBuffers();
    }

private:
    void genVertices(float size)
    {

        vertices = {
            0.0f, size / 2.0f, 0.0f,        // Top-Left
            size / 2.0f, size / 2.0f, 0.0f, // Top-Right
            0.0f, 0.0f, 0.0f,               // Bottom-Left
            size / 2.0f, 0.0f, 0.0f         // Bottom-Right
        };
    }

    void genIndices()
    {
        indices = {
            0, 2, 3,
            0, 3, 1};
    }

    void genColors(glm::vec3 color)
    {
        colors.clear();
        colors.reserve(12);

        for (int i = 0; i < 4; ++i)
        {
            colors.push_back(color.x);
            colors.push_back(color.y);
            colors.push_back(color.z);
        }
    }

    void genTextureVertices(float size)
    {
        texCoords = {
            0.0f, 1.0f, // UV Top-Left
            1.0f, 1.0f, // UV Top-Right
            0.0f, 0.0f, // UV Bottom-Left
            1.0f, 0.0f  // UV Bottom-Right
        };
    }
};