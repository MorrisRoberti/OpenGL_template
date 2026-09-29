#include "../include/InstancedModel.hpp"

InstancedModel::InstancedModel(const std::string &fileName,
                               const std::vector<glm::mat4> &&modelMatrices)
{
    mModelMatrices = std::move(modelMatrices);

    load(fileName);
}

void InstancedModel::load(const std::string &fileName)
{
    clear();
    mModelLoader.load(fileName);
    mModelData = mModelLoader.getModelData();

    setMatrixBuffer();
}

void InstancedModel::render(const RenderContext &context)
{

    for (const auto &mesh : mModelData.mMeshes)
        mesh.renderInstanced(mModelMatrices.size());
}

int InstancedModel::getInstanceCount() const { return mModelMatrices.size(); }

void InstancedModel::setModelMatrices(const std::vector<glm::mat4> &modelMatrices)
{
    if (modelMatrices.empty())
        return;

    mModelMatrices = modelMatrices;
    setMatrixBuffer();
}

const std::vector<glm::mat4> &InstancedModel::getModelMatrices() const
{
    return mModelMatrices;
}

void InstancedModel::setMatrixBuffer()
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, mModelMatrices.size() * sizeof(glm::mat4),
                 &mModelMatrices[0], GL_STATIC_DRAW);

    for (auto &mesh : mModelData.mMeshes)
        mesh.setInsancedAttribs();
}

void InstancedModel::clear() { mModelData.clear(); }
