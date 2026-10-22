#include "Shape.hpp"

#include "RenderContext.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Viewable.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <algorithm>

unsigned int Shape::getVBO() const
{
    return mVbo;
}

unsigned int Shape::getVAO() const
{
    return mVao;
}

unsigned int Shape::getEBO() const
{
    return mEbo;
}

int Shape::getIndexCount() const
{
    return mIndices.size();
}

int Shape::getVertexCount() const
{
    return mVertices.size();
}

void Shape::render(const RenderContext &context)
{
    glm::mat4 currentModelMatrix = context.modelMatrix * getModelMatrix();

    context.shader.setMat4("model", currentModelMatrix);
    context.shader.setUniform1i("gSampler", 0);

    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Shape::~Shape()
{
    if (mVbo)
        glDeleteBuffers(1, &mVbo);
    if (mVao)
        glDeleteBuffers(1, &mVao);
    if (mEbo)
        glDeleteBuffers(1, &mEbo);
}

Shape::Shape(int indexCount, int vertexCount)
{
    mVertices.reserve(vertexCount);
    mIndices.reserve(indexCount);
}

void Shape::setBuffers()
{

    // vao setting
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // vbo setting
    if (!mVertices.empty())
    {

        glGenBuffers(1, &mVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            Vertex::posOffset());

        // setting colors
        if (std::all_of(mVertices.begin(), mVertices.end(), [](const auto &v)
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
        if (std::all_of(mVertices.begin(), mVertices.end(), [](const Vertex &v)
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
        if (!mIndices.empty())
        {
            glGenBuffers(1, &mEbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);
        }
    }

    glBindVertexArray(0);
}