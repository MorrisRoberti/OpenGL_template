#pragma once
#include "Renderable.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"
#include "Vertex.hpp"

#include <vector>

class RenderContext;

class Mesh : public Transformable, public Renderable
{
public:
  Mesh() = default;

  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
       const std::vector<Texture> &textures);

  void render(const RenderContext &context) override;

  void renderInstanced(int instancesCount) const;

  void setInsancedAttribs();

  const unsigned int getVao() const;

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  std::vector<Vertex> mVertices;
  std::vector<unsigned int> mIndices;
  std::vector<Texture> mTextures;

private:
  void init();
};
