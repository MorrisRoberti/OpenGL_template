#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "./Texture.hpp"

class Shape
{
public:
    GLuint getVBO() const
    {
        return vbo;
    }

    GLuint getVAO() const
    {
        return vao;
    }

    GLuint getEBO() const
    {
        return ebo;
    }

    int getIndexCount() const
    {
        return indexCount;
    }

    const glm::mat4 getModelMatrix()
    {
        if (dirty)
        {
            glm::mat4 t = glm::translate(glm::mat4{1.f}, position);
            glm::mat4 r = glm::mat4_cast(rotation);
            glm::mat4 s = glm::scale(glm::mat4{1.f}, mScale);

            cachedModelMatrix = t * r * s;
            dirty = false;
        }

        return cachedModelMatrix;
    }

    int getVertexCount() const
    {
        return vertexCount;
    }

    void translate(glm::vec3 translation)
    {
        position += translation;
        dirty = true;
    }

    void setPosition(glm::vec3 newPos)
    {
        position = newPos;
        dirty = true;
    }

    void scale(glm::vec3 scaling)
    {
        mScale += scaling;
        dirty = true;
    }

    void setScale(glm::vec3 newScale)
    {
        mScale = newScale;
        dirty = true;
    }

    void rotate(glm::vec3 axis, float angle)
    {
        glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

        rotation = deltaRotation * rotation;

        rotation = glm::normalize(rotation);
        dirty = true;
    }

    ~Shape()
    {
        if (vbo)
            glDeleteBuffers(1, &vbo);
        if (vao)
            glDeleteBuffers(1, &vao);
        if (ebo)
            glDeleteBuffers(1, &ebo);
        if (colorBuffer)
            glDeleteBuffers(1, &colorBuffer);
        if (vboTex)
            glDeleteBuffers(1, &vboTex);
    }

protected:
    Shape() = default;

    Shape(int iCount, int vCount) : indexCount(iCount), vertexCount(vCount) {}

    void setBuffers()
    {

        // vao setting
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // vbo setting
        if (!vertices.empty())
        {

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *)0);
        }
        // set the color buffer
        if (!colors.empty())
        {

            glGenBuffers(1, &colorBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *)0);
        }

        // set the texture buffer
        if (!texCoords.empty())
        {

            glGenBuffers(1, &vboTex);
            glBindBuffer(GL_ARRAY_BUFFER, vboTex);
            glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vboTex);
            glVertexAttribPointer(
                1,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *)0);
        }

        // ebo setting
        if (!indices.empty())
        {
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        }

        glBindVertexArray(0);
    }

    int indexCount;
    int vertexCount;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint colorBuffer;
    GLuint vboTex;

    Texture *texture;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;

    glm::vec3 position{0.f};
    glm::vec3 mScale{1.f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::mat4 cachedModelMatrix{1.0f};

    bool dirty{false};
};
