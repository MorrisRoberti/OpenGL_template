#pragma once
#include <string>

class Texture
{

public:
    Texture() = default;

    Texture(unsigned int textureTarget, const std::string &fileName) : mTextureTarget(textureTarget), mFileName(fileName)
    {
        load();
    }

    bool load();

    void bind(unsigned int textureUnit);

private:
    unsigned int mTextureTarget;
    std::string mFileName;
    unsigned int mTextureObject;
};