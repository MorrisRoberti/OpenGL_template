#pragma once
#include <GL/glew.h>
#include "./Loadable.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/type_ptr.hpp>
#include "./Mesh.hpp"

struct ModelData
{
    std::vector<Mesh> mMeshes;
    std::vector<Texture> mTextures;
    std::string mFileName;

    // define the assignment operator (even better if movable)

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