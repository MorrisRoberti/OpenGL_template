#pragma once
#include <GL/glew.h>

class Vertex
{
public:
    Vertex() = default;

    Vertex(glm::vec3 posCoords, glm::vec2 texCoords, glm::vec3 normals) : mPos(posCoords), mTexCoords(texCoords), mNormals(normals) {}

private:
    glm::vec3 mPos{0.f};
    glm::vec2 mTexCoords{0.f};
    glm::vec3 mNormals{0.f};
};
