#pragma once
#include "Loadable.hpp"
#include "Mesh.hpp"
#include "ModelData.hpp"
#include "Texture.hpp"

#include <assimp/material.h>

#include <string>
#include <vector>

class aiScene;
class aiMesh;
class aiMaterial;

class ModelLoader : public Loadable
{

public:
    ModelLoader() = default;

    void load(const std::string &fileName) override;

    const ModelData getModelData() const;

private:
    void initFromScene(const aiScene *scene);
    std::vector<Texture> initMaterials(aiMaterial *mat, aiTextureType type);
    Mesh initMesh(int index, const aiMesh *mesh, const aiScene *scene);

    ModelData mModelData;
};