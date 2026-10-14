#pragma once

#include "ModelData.hpp"
#include "ModelLoader.hpp"
#include "Renderable.hpp"
#include "Transformable.hpp"

#include <string>
#include <vector>

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