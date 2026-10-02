#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

#include "./Loadable.hpp"
#include "./Mesh.hpp"
#include <assimp/material.h>

class aiScene;
class aiMesh;
class aiMaterial;

struct ModelData
{
    std::vector<Mesh> mMeshes;
    std::vector<Texture> mTextures;
    std::string mFileName;

    void clear()
    {
        mMeshes.clear();
        mTextures.clear();
        mFileName.clear();
    }
};

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

    ModelData modelData;
};