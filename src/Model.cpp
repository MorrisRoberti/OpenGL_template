#include "../include/Model.hpp"

Model::Model(const std::string &fileName)
{
    load(fileName);
}

void Model::load(const std::string &fileName)
{
    clear();
    mModelLoader.load(fileName);
    mModelData = mModelLoader.getModelData();
}

void Model::render(const RenderContext &context)
{

    RenderContext newContext = context;

    newContext.modelMatrix = context.modelMatrix * getModelMatrix();

    for (auto &mesh : mModelData.mMeshes)
        mesh.render(newContext);
}

void Model::clear()
{
    mModelData.clear();
}
