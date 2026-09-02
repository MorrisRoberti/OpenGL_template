#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../include/Model.hpp"

Model::Model(const std::string &fileName)
{
    load(fileName);
}

bool Model::load(const std::string &fileName)
{
    bool res = false;

    clear();

    Assimp::Importer importer;

    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (pScene)
        res = initFromScene(pScene, fileName);
    else
        std::cerr << "Error while parsing the model at: " << fileName << std::endl;

    return res;
}

void Model::render(RenderContext &context)
{

    // glm::mat4 oldModelMatrix = context.modelMatrix;

    // context.modelMatrix = context.modelMatrix * getModelMatrix();

    // for (auto &mesh : mEntries)
    // {
    //     mesh.render(context);
    // }

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);

    // context.modelMatrix = oldModelMatrix;
}
void Model::clear()
{
    mEntries.clear();
    mTextures.clear();
}

bool Model::initFromScene(const aiScene *scene, const std::string &fileName)
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

bool Model::initMaterials(const aiScene *scene, const std::string &fileName)
{
    bool res = false;
    std::string dir;

    // find the object directory
    std::size_t lastSlash = fileName.find_last_of("/\\");
    if (lastSlash != std::string::npos)
    {
        dir = fileName.substr(0, lastSlash);
    }
    else
    {
        dir = ".";
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
    {
        const aiMaterial *pMaterial = scene->mMaterials[i];
        mTextures.at(i) = nullptr;
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS)
            {
                std::string FullPath = dir + "/" + Path.data;
                mTextures.at(i) = new Texture{GL_TEXTURE_2D, FullPath};

                if (!mTextures.at(i)->load())
                {
                    std::cerr << "Error loading texture " << FullPath << std::endl;
                    delete mTextures.at(i);
                    mTextures.at(i) = nullptr;
                    res = false;
                }
            }
        }
        // fallback
        if (!mTextures.at(i))
        {
            mTextures.at(i) = new Texture{GL_TEXTURE_2D, "./assets/textures/default.png"};
            res = mTextures.at(i)->load();
        }
    }

    return res;
}

void Model::initMesh(int index, const aiMesh *mesh)
{
    mEntries.at(index).materialIndex = mesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

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

    mEntries.at(index).init(vertices, indices);
}
