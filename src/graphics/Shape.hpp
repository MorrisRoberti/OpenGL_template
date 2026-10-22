#pragma once
#include "Renderable.hpp"
#include "Transformable.hpp"
#include "Vertex.hpp"

#include <vector>

class Texture;
struct RenderContext;

class Shape : public Transformable, public Renderable
{
public:
    unsigned int getVBO() const;

    unsigned int getVAO() const;

    unsigned int getEBO() const;

    int getIndexCount() const;

    int getVertexCount() const;

    void render(const RenderContext &context) override;

    ~Shape();

protected:
    Shape() = default;

    Shape(int indexCount, int vertexCount);

    void setBuffers();

    unsigned int mVbo;
    unsigned int mVao;
    unsigned int mEbo;

    Texture *mTexture;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};
