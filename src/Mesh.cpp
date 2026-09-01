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

void Mesh::render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < mEntries.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mEntries[i].VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEntries[i].EBO);

        const unsigned int materialIndex = mEntries[i].materialIndex;

        if (materialIndex < mTextures.size() && mTextures[materialIndex])
        {
            mTextures[materialIndex]->bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, mEntries[i].numIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
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
    bool res = false;
    std::string dir = "../assets/textures";

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
                mTextures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!mTextures[i]->load())
                {
                    std::cerr << "Error loading texture " << FullPath << std::endl;
                    delete mTextures[i];
                    mTextures[i] = nullptr;
                    res = false;
                }
            }
        }
        // if (!mTextures[i])
        // {
        //     mTextures[i] = new Texture(GL_TEXTURE_2D, "../assets/textures/white.png");
        //     res = mTextures[i]->load();
        // }
    }

    return res;
}

void Mesh::initMesh(int index, const aiMesh *mesh)
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

    mEntries[index].init(vertices, indices);
}
