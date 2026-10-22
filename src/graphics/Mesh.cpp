#include "Mesh.hpp"

#include "RenderContext.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <vector>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures)
{
    mVertices = vertices;
    mIndices = indices;
    mTextures = textures;
    init();
}

void Mesh::render(const RenderContext &context)
{

    glm::mat4 currentModelMatrix = context.mModelMatrix * getModelMatrix();

    context.mShader.setMat4("model", currentModelMatrix);
    context.mShader.setUniform1i("gSampler", 0);

    for (size_t i = 0; i < mTextures.size(); ++i)
    {
        mTextures[i].bind(GL_TEXTURE0 + i);
    }

    // draw mesh
    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::renderInstanced(int instancesCount) const
{
    glBindVertexArray(mVao);

    glDrawElementsInstanced(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0,
                            instancesCount);
    glBindVertexArray(0);
}

void Mesh::setInsancedAttribs()
{

    for (size_t i = 0; i < mTextures.size(); ++i)
    {
        mTextures[i].bind(GL_TEXTURE0 + i);
    }

    glBindVertexArray(mVao);

    std::size_t vec4Size = sizeof(glm::vec4);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)0);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void *)(1 * vec4Size));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void *)(2 * vec4Size));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size,
                          (void *)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}

void Mesh::init()
{

    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);
    glGenBuffers(1, &mEbo);

    glBindVertexArray(mVao);

    // mVbo setting
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(),
                 &mVertices.at(0), GL_STATIC_DRAW);

    // mEbo setting
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * mIndices.size(), &mIndices.at(0),
                 GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          Vertex::posOffset());
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          Vertex::normalsOffset());
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          Vertex::texCoordsOffset());

    glBindVertexArray(0);
}