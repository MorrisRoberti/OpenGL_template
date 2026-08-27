#include "../include/Texture.hpp"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

bool Texture::load()
{
    stbi_set_flip_vertically_on_load(1);
    int width = 0;
    int height = 0;
    int bbp = 0;
    auto image_data = stbi_load(mFileName.c_str(), &width, &height, &bbp, 0);

    if (!image_data)
    {
        std::cerr << "Can't load the texture from: " << mFileName << std::endl;
        exit(0);
    }

    glGenTextures(1, &mTextureObject);
    glBindTexture(mTextureTarget, mTextureObject);
    if (mTextureTarget == GL_TEXTURE_2D)
    {
        glTexImage2D(mTextureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    else
    {
        std::cout << "Type of texture target not supported" << std::endl;
    }

    glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(mTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(mTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glBindTexture(mTextureTarget, 0);

    stbi_image_free(image_data);

    return true;
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(mTextureTarget, mTextureObject);
}