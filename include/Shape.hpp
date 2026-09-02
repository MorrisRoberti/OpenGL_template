#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "./Texture.hpp"
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./RenderContext.hpp"

class Shape : public Transformable, public Renderable
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

    int getVertexCount() const
    {
        return vertexCount;
    }

    void render(RenderContext &context) override
    {
        glm::mat4 currentModelMatrix = context.modelMatrix * getModelMatrix();

        context.shader.setMat4("model", currentModelMatrix);
        context.shader.setUniform1i("gSampler", 0);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
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
};
