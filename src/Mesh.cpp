#include "../include/Mesh.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Mesh::Mesh(const std::string &fileName)
{
    load(fileName);
}

bool Mesh::load(const std::string &fileName)
{
    bool res = false;

    clear();

    Assimp::Importer importer;

    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    if (pScene)
        res = initFromScene(pScene, fileName);
    else
        std::cerr << "Error while parsing the mesh at: " << fileName << std::endl;

    return res;
}

void Mesh::clear()
{
    mEntries.clear();
    mTextures.clear();
}

bool Mesh::initFromScene(const aiScene *scene, const std::string &fileName)
{
    mEntries.resize(scene->mNumMeshes);
    mTextures.resize(scene->mNumMaterials);

    for (size_t i = 0; i < mEntries.size(); ++i)
    {
        const aiMesh *mesh = scene->mMeshes[i];
        initMesh(i, mesh);
    }

    return initMaterials(scene, fileName);
}

bool Mesh::initMaterials(const aiScene *scene, const std::string &fileName)
{

    return false;
}

void Mesh::initMesh(int index, const aiMesh *mesh)
{
    mEntries.at(index).materialIndex = mesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<aiFace> indices;

    const aiVector3D zero3D{0.f, 0.f, 0.f};

    // loading vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        const aiVector3D *pos = &(mesh->mVertices[i]);
        const aiVector3D *normal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &zero3D;
        const aiVector3D *texCoords = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero3D;

        Vertex v{glm::vec3{pos->x, pos->y, pos->z},
                 glm::vec2{texCoords->x, texCoords->y},
                 glm::vec3{normal->x, normal->y, normal->z}};

        vertices.push_back(v);
    }

    // loading indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        const aiFace &face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    mEntries[index].init(vertices, indices);
}
