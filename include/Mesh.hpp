#pragma once
#include <GL/glew.h>
#include <vector>
#include "./Texture.hpp"
#include "./Vertex.hpp"
#include "./Transformable.hpp"
#include "./Renderable.hpp"

class Mesh : public Transformable, public Renderable
{
public:
    Mesh() = default;

    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<unsigned int> &indices,
         const std::vector<Texture> &textures) : mVertices(vertices),
                                                 mIndices(indices), mTextures(textures)
    {
        init();
    };

    void render(const RenderContext &context) override
    {
        glm::mat4 currentModelMatrix = context.modelMatrix * getModelMatrix();

        context.shader.setMat4("model", currentModelMatrix);
        context.shader.setUniform1i("gSampler", 0);

        for (size_t i = 0; i < mTextures.size(); ++i)
        {
            mTextures[i].bind(GL_TEXTURE0 + i);
        }

        // draw mesh
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;

private:
    void init()
    {

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        // vbo setting
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(Vertex) * mVertices.size(),
                     &mVertices.at(0),
                     GL_STATIC_DRAW);

        // ebo setting
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(unsigned int) * mIndices.size(),
                     &mIndices.at(0),
                     GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mNormals));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mTexCoords));

        glBindVertexArray(0);
    }
};