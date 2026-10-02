#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./Texture.hpp"
#include "./Vertex.hpp"

class RenderContext;

class Mesh : public Transformable, public Renderable
{
public:
  Mesh() = default;

  Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
       const std::vector<Texture> &textures);

  void render(const RenderContext &context) override;

  void renderInstanced(int instancesCount) const;

  void setInsancedAttribs();

  const GLuint getVao() const;

  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  std::vector<Vertex> mVertices;
  std::vector<GLuint> mIndices;
  std::vector<Texture> mTextures;

private:
  void init();
};
