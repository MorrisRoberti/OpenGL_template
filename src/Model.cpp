#include "../include/Model.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/gtc/type_precision.hpp>

Model::Model(const std::string &fileName)
{
    mFileName = fileName;
    load(fileName);
}

void Model::load(const std::string &fileName)
{
    clear();

    mFileName = fileName;

    Assimp::Importer importer;

    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (pScene)
        initFromScene(pScene);
    else
        std::cerr << "Error while parsing the model at: " << fileName << std::endl;
}

void Model::render(const RenderContext &context)
{

    RenderContext newContext = context;

    newContext.modelMatrix = context.modelMatrix * getModelMatrix();

    for (auto &mesh : mMeshes)
        mesh.render(newContext);
}

void Model::clear()
{
    mMeshes.clear();
    mTextures.clear();
    mFileName.clear();
}

void Model::initFromScene(const aiScene *scene)
{
    mMeshes.resize(scene->mNumMeshes);
    mTextures.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMeshes; ++i)
    {
        const aiMesh *mesh = scene->mMeshes[i];
        auto createdMesh = initMesh(i, mesh, scene);
        mMeshes.push_back(createdMesh);
    }
}

std::vector<Texture> Model::initMaterials(aiMaterial *mat, aiTextureType type)
{
    std::vector<Texture> textures;
    textures.reserve(mat->GetTextureCount(type));
    std::string dir;

    // find the object directory
    std::size_t lastSlash = mFileName.find_last_of("/\\");
    if (lastSlash != std::string::npos)
    {
        dir = mFileName.substr(0, lastSlash);
    }
    else
    {
        dir = ".";
    }

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture{GL_TEXTURE_2D, dir + '/' + str.C_Str()};
        textures.push_back(texture);
    }

    return textures;
}

Mesh Model::initMesh(int index, const aiMesh *mesh, const aiScene *scene)
{

    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    std::vector<unsigned int> indices;
    indices.reserve(mesh->mNumFaces * 3);

    std::vector<Texture> textures;

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

    // initializing and attaching the textures
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = initMaterials(material,
                                                         aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = initMaterials(material,
                                                          aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh{
        vertices,
        indices,
        textures};
}
