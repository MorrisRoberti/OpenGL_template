#pragma once
#include <string>
#include <vector>

#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./ModelLoader.hpp"

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