#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/gtc/type_precision.hpp>
#include "./Texture.hpp"
#include "./Shape.hpp"

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

class Mesh : public Shape
{

public:
    Mesh(const std::string &fileName);

    bool load(const std::string &fileName);

    void render();

private:
    void clear();

    bool initFromScene(const aiScene *scene, const std::string &fileName);
    bool initMaterials(const aiScene *scene, const std::string &fileName);
    void initMesh(int index, const aiMesh *mesh);

    struct MeshEntry
    {
        MeshEntry() = default;

        bool init(const std::vector<Vertex> &vertices,
                  const std::vector<unsigned int> &indices)
        {

            numIndices = indices.size();

            // 1. Generazione e popolamento del Vertex Buffer Object (VBO)
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(Vertex) * vertices.size(),
                         &vertices[0],
                         GL_STATIC_DRAW);

            // 2. Generazione e popolamento dell'Index Buffer Object (IBO)
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(unsigned int) * numIndices,
                         &indices[0],
                         GL_STATIC_DRAW);
            return true;
        }

        GLuint VBO;
        GLuint EBO;
        unsigned int numIndices;
        unsigned int materialIndex;
    };

    std::vector<MeshEntry> mEntries;
    std::vector<Texture *> mTextures;
};