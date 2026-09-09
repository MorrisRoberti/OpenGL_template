#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include "./Texture.hpp"
#include "./Vertex.hpp"
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
        return indices.size();
    }

    int getVertexCount() const
    {
        return vertices.size();
    }

    void render(const RenderContext &context) override
    {
        glm::mat4 currentModelMatrix = context.modelMatrix * getModelMatrix();

        context.shader.setMat4("model", currentModelMatrix);
        context.shader.setUniform1i("gSampler", 0);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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
    }

protected:
    Shape() = default;

    Shape(int iCount, int vCount)
    {
        vertices.reserve(vCount);
        indices.reserve(iCount);
    }

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
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                Vertex::posOffset());

            // setting colors
            if (std::all_of(vertices.begin(), vertices.end(), [](const auto &v)
                            { return v.hasColors(); }))
            {
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                    1,
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(Vertex),
                    Vertex::colorOffset());
            }

            // set the texture buffer
            if (std::all_of(vertices.begin(), vertices.end(), [](const Vertex &v)
                            { return v.hasTexCoords(); }))
            {
                std::cout << "in tex setting" << std::endl;
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(
                    2,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(Vertex),
                    Vertex::texCoordsOffset());
            }

            // ebo setting
            if (!indices.empty())
            {
                glGenBuffers(1, &ebo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
            }
        }

        glBindVertexArray(0);
    }

    GLuint vbo;
    GLuint vao;
    GLuint ebo;

    Texture *texture;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};
