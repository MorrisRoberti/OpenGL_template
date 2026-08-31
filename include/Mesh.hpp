#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/gtc/type_precision.hpp>
#include "./Texture.hpp"

class Vertex
{
public:
    Vertex() = default;

    Vertex(glm::vec3 posCoords, glm::vec2 texCoords, glm::vec3 normals) : mPos(posCoords), mTexCoords(texCoords), mNormals(normals) {}

private:
    glm::vec3 mPos{0.f};
    glm::vec2 mTexCoords{0.f};
    glm::vec3 mNormals{0.f};
};

class Mesh
{

public:
    Mesh(const std::string &fileName);

    bool load(const std::string &fileName);

private:
    void clear();

    bool initFromScene(const aiScene *scene, const std::string &fileName);
    bool initMaterials(const aiScene *scene, const std::string &fileName);
    void initMesh(int index, const aiMesh *mesh);

    struct MeshEntry
    {
        MeshEntry() = default;

        // bool Init(const std::vector &Vertices,
        //   const std::vector &Indices);

        GLuint VBO;
        GLuint EBO;
        unsigned int numIndices;
        unsigned int materialIndex;
    };

    std::vector<MeshEntry> mEntries;
    std::vector<Texture> mTextures;
};