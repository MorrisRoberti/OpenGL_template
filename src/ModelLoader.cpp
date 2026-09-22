#include "../include/ModelLoader.hpp"

void ModelLoader::load(const std::string &fileName)
{

    modelData.mFileName = fileName;

    Assimp::Importer importer;

    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (pScene)
    {

        initFromScene(pScene);
        modelData.mFileName.clear();
    }
    else
        std::cerr << "Error while parsing the model at: " << fileName << std::endl;
}

const ModelData ModelLoader::getModelData() const
{
    return modelData;
}

void ModelLoader::initFromScene(const aiScene *scene)
{
    modelData.mMeshes.resize(scene->mNumMeshes);
    modelData.mTextures.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMeshes; ++i)
    {
        const aiMesh *mesh = scene->mMeshes[i];
        auto createdMesh = initMesh(i, mesh, scene);
        modelData.mMeshes.push_back(createdMesh);
    }
}

std::vector<Texture> ModelLoader::initMaterials(aiMaterial *mat, aiTextureType type)
{
    std::vector<Texture> textures;
    textures.reserve(mat->GetTextureCount(type));
    std::string dir;

    // find the object directory
    std::size_t lastSlash = modelData.mFileName.find_last_of("/\\");
    if (lastSlash != std::string::npos)
    {
        dir = modelData.mFileName.substr(0, lastSlash);
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

Mesh ModelLoader::initMesh(int index, const aiMesh *mesh, const aiScene *scene)
{

    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    std::vector<GLuint> indices;
    indices.reserve(mesh->mNumFaces * 3);

    std::vector<Texture> textures;

    const aiVector3D zero3D{0.f, 0.f, 0.f};

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        const aiVector3D *pos = &(mesh->mVertices[i]);

        std::optional<glm::vec2> texCoords{std::nullopt};
        if (mesh->HasTextureCoords(0))
            texCoords = glm::vec2{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};

        std::optional<glm::vec3> normal{std::nullopt};
        if (mesh->HasNormals())
            normal = glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        Vertex v{
            glm::vec3{pos->x, pos->y, pos->z},
            texCoords,
            normal,
            std::nullopt};

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
