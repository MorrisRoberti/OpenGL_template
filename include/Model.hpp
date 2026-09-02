#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/gtc/type_precision.hpp>
#include "./Texture.hpp"
#include "./Shape.hpp"
#include "./Vertex.hpp"
#include "./Mesh.hpp"

class Model : public Shape
{

public:
    Model(const std::string &fileName);

    bool load(const std::string &fileName);

    void render();

private:
    void clear();

    bool initFromScene(const aiScene *scene, const std::string &fileName);
    bool initMaterials(const aiScene *scene, const std::string &fileName);
    void initMesh(int index, const aiMesh *mesh);

    std::vector<Mesh> mEntries;
    std::vector<Texture *> mTextures;
};