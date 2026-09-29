#pragma once
#include <GL/glew.h>
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./RenderContext.hpp"
#include "./ModelLoader.hpp"

struct ModelData;
class InstancedModel : public Renderable
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