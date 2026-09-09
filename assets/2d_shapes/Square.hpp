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
        float halfSize{size / 2.0f};

        vertices.clear();
        vertices.reserve(4);

        // Creiamo i vertici passando solo la posizione; gli altri campi restano std::nullopt
        vertices.push_back(Vertex{glm::vec3{0.0f, halfSize, 0.0f}, std::nullopt, std::nullopt, std::nullopt});     // Top-Left
        vertices.push_back(Vertex{glm::vec3{halfSize, halfSize, 0.0f}, std::nullopt, std::nullopt, std::nullopt}); // Top-Right
        vertices.push_back(Vertex{glm::vec3{0.0f, 0.0f, 0.0f}, std::nullopt, std::nullopt, std::nullopt});         // Bottom-Left
        vertices.push_back(Vertex{glm::vec3{halfSize, 0.0f, 0.0f}, std::nullopt, std::nullopt, std::nullopt});     // Bottom-Right
    }

    void genIndices()
    {
        indices = {
            0, 2, 3,
            0, 3, 1};
    }

    void genColors(glm::vec3 color)
    {
        for (auto &vertex : vertices)
        {
            vertex.mColor = color; // Assegna il valore all'std::optional
        }
    }

    void genTextureVertices(float size)
    {
        if (vertices.size() >= 4)
        {
            vertices[0].mTexCoords = glm::vec2{0.0f, 1.0f}; // UV Top-Left
            vertices[1].mTexCoords = glm::vec2{1.0f, 1.0f}; // UV Top-Right
            vertices[2].mTexCoords = glm::vec2{0.0f, 0.0f}; // UV Bottom-Left
            vertices[3].mTexCoords = glm::vec2{1.0f, 0.0f}; // UV Bottom-Right
        }
    }
};