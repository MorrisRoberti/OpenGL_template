#pragma once
#include <GL/glew.h>
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./RenderContext.hpp"
#include "./ModelLoader.hpp"

struct ModelData;
class InstancedModel : public Transformable, public Renderable
{
public:
    InstancedModel(const std::string &fileName, int instancesCount);

    InstancedModel(const std::string &fileName, const std::vector<glm::mat4> &&modelMatrices);

    void load(const std::string &fileName);

    void render(const RenderContext &context) override;

    void setInstanceCount(int newCount);

    int getInstanceCount() const;

    // we want the possibility to individually set the position, rotation etc.
    // void setModelMatrices();

private:
    void clear();

    ModelLoader mModelLoader;
    ModelData mModelData;
    std::vector<glm::mat4> mModelMatrices;
    int mInstancesCount{1};
};