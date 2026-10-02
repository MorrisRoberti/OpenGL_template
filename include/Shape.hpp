#pragma once
#include <vector>
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./Vertex.hpp"

class Texture;
struct RenderContext;

class Shape : public Transformable, public Renderable
{
public:
    GLuint getVBO() const;

    GLuint getVAO() const;

    GLuint getEBO() const;

    int getIndexCount() const;

    int getVertexCount() const;

    void render(const RenderContext &context) override;

    ~Shape();

protected:
    Shape() = default;

    Shape(int iCount, int vCount);

    void setBuffers();

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

    Texture *texture;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
