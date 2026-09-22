#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "./Texture.hpp"
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./RenderContext.hpp"
#include "./Mesh.hpp"
#include "./ModelLoader.hpp"

struct ModelData;
class Model : public Transformable, public Renderable
{

public:
    Model(const std::string &fileName);

    void load(const std::string &fileName);

    void render(const RenderContext &context) override;

private:
    void clear();

    ModelLoader mModelLoader;
    ModelData mModelData;
};