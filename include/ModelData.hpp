#pragma once
#include <string>
#include <vector>

#include "./Texture.hpp"
#include "./Mesh.hpp"

struct ModelData
{
    std::vector<Mesh> mMeshes;
    std::vector<Texture> mTextures;
    std::string mFileName;

    void clear()
    {
        mMeshes.clear();
        mTextures.clear();
        mFileName.clear();
    }
};