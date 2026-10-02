#pragma once
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./ModelLoader.hpp"
#include "./ModelData.hpp"

class InstancedModel : public Transformable, public Renderable
{
public:
    InstancedModel(const std::string &fileName, const std::vector<glm::mat4> &&modelMatrices);

    void load(const std::string &fileName);

    void render(const RenderContext &context) override;

    int getInstanceCount() const;

    void setModelMatrices(const std::vector<glm::mat4> &modelMatrices);

    const std::vector<glm::mat4> &getModelMatrices() const;

private:
    void clear();

    void setMatrixBuffer();

    ModelLoader mModelLoader;
    ModelData mModelData;
    std::vector<glm::mat4> mModelMatrices;
};