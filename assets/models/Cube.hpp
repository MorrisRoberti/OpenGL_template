#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <array>
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
        float half{size / 2.0f};

        vertices.clear();
        vertices.reserve(24);

        const std::array<glm::vec3, 24> positions{
            // Front
            glm::vec3{-half, half, half},  // Top-Left
            glm::vec3{half, half, half},   // Top-Right
            glm::vec3{-half, -half, half}, // Bottom-Left
            glm::vec3{half, -half, half},  // Bottom-Right

            // Back
            glm::vec3{half, half, -half},   // Top-Left
            glm::vec3{-half, half, -half},  // Top-Right
            glm::vec3{half, -half, -half},  // Bottom-Left
            glm::vec3{-half, -half, -half}, // Bottom-Right

            // Left
            glm::vec3{-half, half, -half},  // Top-Left
            glm::vec3{-half, half, half},   // Top-Right
            glm::vec3{-half, -half, -half}, // Bottom-Left
            glm::vec3{-half, -half, half},  // Bottom-Right

            // Right
            glm::vec3{half, half, half},   // Top-Left
            glm::vec3{half, half, -half},  // Top-Right
            glm::vec3{half, -half, half},  // Bottom-Left
            glm::vec3{half, -half, -half}, // Bottom-Right

            // Top
            glm::vec3{-half, half, -half}, // Top-Left
            glm::vec3{half, half, -half},  // Top-Right
            glm::vec3{-half, half, half},  // Bottom-Left
            glm::vec3{half, half, half},   // Bottom-Right

            // Bottom
            glm::vec3{-half, -half, half},  // Top-Left
            glm::vec3{half, -half, half},   // Top-Right
            glm::vec3{-half, -half, -half}, // Bottom-Left
            glm::vec3{half, -half, -half}   // Bottom-Right
        };

        for (const auto &pos : positions)
        {
            vertices.push_back(Vertex{pos, std::nullopt, std::nullopt, std::nullopt});
        }
    }

    void genIndices()
    {
        indices.clear();
        indices.reserve(36);

        for (unsigned int i = 0; i < 6; ++i)
        {
            unsigned int offset{i * 4};

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
        for (auto &vertex : vertices)
        {
            vertex.mColor = color;
        }
    }

    void genTextureVertices()
    {
        for (size_t i = 0; i < 6; ++i)
        {
            size_t offset{i * 4};
            if (offset + 3 < vertices.size())
            {
                vertices[offset + 0].mTexCoords = glm::vec2{0.0f, 1.0f}; // UV Top-Left
                vertices[offset + 1].mTexCoords = glm::vec2{1.0f, 1.0f}; // UV Top-Right
                vertices[offset + 2].mTexCoords = glm::vec2{0.0f, 0.0f}; // UV Bottom-Left
                vertices[offset + 3].mTexCoords = glm::vec2{1.0f, 0.0f}; // UV Bottom-Right
            }
        }
    }
};