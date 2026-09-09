#pragma once
#include <GL/glew.h>
#include <optional>

class Vertex
{
public:
    Vertex() = default;

    Vertex(glm::vec3 posCoords, std::optional<glm::vec2> texCoords, std::optional<glm::vec3> normals, std::optional<glm::vec3> color)
    {
        mPos = posCoords;
        if (texCoords.has_value())
            mTexCoords = texCoords;
        if (normals.has_value())
            mNormals = normals;
        if (color.has_value())
            mColor = color;
    }

    bool hasTexCoords() const
    {
        return mTexCoords.has_value();
    }

    bool hasNormals() const
    {
        return mNormals.has_value();
    }

    bool hasColors() const
    {
        return mColor.has_value();
    }

    static constexpr const void *posOffset() noexcept
    {
        return reinterpret_cast<const void *>(0);
    }

    static constexpr const void *texCoordsOffset() noexcept
    {
        return reinterpret_cast<const void *>(sizeof(glm::vec3));
    }

    static constexpr const void *normalsOffset() noexcept
    {
        return reinterpret_cast<const void *>(
            sizeof(glm::vec3) + sizeof(std::optional<glm::vec2>));
    }

    static constexpr const void *colorOffset() noexcept
    {
        return reinterpret_cast<const void *>(
            sizeof(glm::vec3) + sizeof(std::optional<glm::vec2>) + sizeof(std::optional<glm::vec3>));
    }
    glm::vec3 mPos{0.f};
    std::optional<glm::vec2> mTexCoords{0.f};
    std::optional<glm::vec3> mNormals{0.f};
    std::optional<glm::vec3> mColor{0.f};
};
