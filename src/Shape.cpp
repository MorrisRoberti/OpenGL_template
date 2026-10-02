#include <GL/glew.h>

#include <glm/mat4x4.hpp>

#include <algorithm>
#include "../include/Vertex.hpp"
#include "../include/Texture.hpp"
#include "../include/Shape.hpp"
#include "../include/Shader.hpp"
#include "../include/Viewable.hpp"
#include "../include/RenderContext.hpp"

GLuint Shape::getVBO() const
{
    return vbo;
}

GLuint Shape::getVAO() const
{
    return vao;
}

GLuint Shape::getEBO() const
{
    return ebo;
}

int Shape::getIndexCount() const
{
    return indices.size();
}

int Shape::getVertexCount() const
{
    return vertices.size();
}

void Shape::render(const RenderContext &context)
{
    glm::mat4 currentModelMatrix = context.modelMatrix * getModelMatrix();

    context.shader.setMat4("model", currentModelMatrix);
    context.shader.setUniform1i("gSampler", 0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Shape::~Shape()
{
    if (vbo)
        glDeleteBuffers(1, &vbo);
    if (vao)
        glDeleteBuffers(1, &vao);
    if (ebo)
        glDeleteBuffers(1, &ebo);
}

Shape::Shape(int iCount, int vCount)
{
    vertices.reserve(vCount);
    indices.reserve(iCount);
}

void Shape::setBuffers()
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
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        }
    }

    glBindVertexArray(0);
}