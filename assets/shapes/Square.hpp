#pragma once
#include "graphics/Shape.hpp"
#include "graphics/Vertex.hpp"
#include "graphics/Texture.hpp"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

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

        mVertices.clear();
        mVertices.reserve(4);

        mVertices.push_back(Vertex{glm::vec3{0.0f, halfSize, 0.0f}, std::nullopt, std::nullopt, std::nullopt});     // Top-Left
        mVertices.push_back(Vertex{glm::vec3{halfSize, halfSize, 0.0f}, std::nullopt, std::nullopt, std::nullopt}); // Top-Right
        mVertices.push_back(Vertex{glm::vec3{0.0f, 0.0f, 0.0f}, std::nullopt, std::nullopt, std::nullopt});         // Bottom-Left
        mVertices.push_back(Vertex{glm::vec3{halfSize, 0.0f, 0.0f}, std::nullopt, std::nullopt, std::nullopt});     // Bottom-Right
    }

    void genIndices()
    {
        mIndices = {
            0, 2, 3,
            0, 3, 1};
    }

    void genColors(glm::vec3 color)
    {
        for (auto &vertex : mVertices)
        {
            vertex.mColor = color;
        }
    }

    void genTextureVertices(float size)
    {
        if (mVertices.size() >= 4)
        {
            mVertices.at(0).mTexCoords = glm::vec2{0.0f, 1.0f}; // UV Top-Left
            mVertices.at(1).mTexCoords = glm::vec2{1.0f, 1.0f}; // UV Top-Right
            mVertices.at(2).mTexCoords = glm::vec2{0.0f, 0.0f}; // UV Bottom-Left
            mVertices.at(3).mTexCoords = glm::vec2{1.0f, 0.0f}; // UV Bottom-Right
        }
    }
};