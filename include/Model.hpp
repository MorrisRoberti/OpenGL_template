#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include "./Texture.hpp"
#include "./Renderable.hpp"
#include "./Transformable.hpp"
#include "./RenderContext.hpp"
#include "./Mesh.hpp"

class Model : public Transformable, public Renderable
{

public:
    Model(const std::string &fileName);

    void load(const std::string &fileName);

    void render(const RenderContext &context) override;

private:
    void clear();

    void initFromScene(const aiScene *scene);
    std::vector<Texture> initMaterials(aiMaterial *mat, aiTextureType type);
    Mesh initMesh(int index, const aiMesh *mesh, const aiScene *scene);

    std::vector<Mesh> mMeshes;
    std::vector<Texture> mTextures;
    std::string mFileName;
};