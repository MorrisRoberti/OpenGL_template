#pragma once
#include <GL/glew.h>
#include <string>

class Texture
{

public:
    Texture() = default;

    Texture(GLenum textureTarget, const std::string &fileName) : mTextureTarget(textureTarget), mFileName(fileName)
    {
        load();
    }

    bool load();

    void bind(GLenum textureUnit);

private:
    GLenum mTextureTarget;
    std::string mFileName;
    GLuint mTextureObject;
};