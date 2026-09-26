#include "../include/InstancedModel.hpp"

InstancedModel::InstancedModel(const std::string &fileName, int instancesCount)
{
    if (instancesCount >= 0)
        mInstancesCount = instancesCount;

    load(fileName);
}

InstancedModel::InstancedModel(const std::string &fileName, const std::vector<glm::mat4> &&modelMatrices)
{
    mInstancesCount = modelMatrices.size();
    mModelMatrices = std::move(modelMatrices);

    load(fileName);
}

void InstancedModel::load(const std::string &fileName)
{
    clear();
    mModelLoader.load(fileName);
    mModelData = mModelLoader.getModelData();

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, mInstancesCount * sizeof(glm::mat4), &mModelMatrices[0], GL_STATIC_DRAW);

    for (auto &mesh : mModelData.mMeshes)
        mesh.setInsancedAttribs();
}

void InstancedModel::render(const RenderContext &context)
{

    for (const auto &mesh : mModelData.mMeshes)
    {
        glBindVertexArray(mesh.getVao());
        glDrawElementsInstanced(
            GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, 0, mInstancesCount);
        glBindVertexArray(0);
    }
}

void InstancedModel::setInstanceCount(int newCount)
{
    if (newCount >= 0)
        mInstancesCount = newCount;
}

int InstancedModel::getInstanceCount() const
{
    return mInstancesCount;
}

void InstancedModel::clear()
{
    mModelData.clear();
}
