#pragma once
#include "Shader.hpp"
#include "Viewable.hpp"

#include <glm/mat4x4.hpp>

struct RenderContext
{
    const Viewable &mCamera;
    Shader &mShader;
    glm::mat4 mModelMatrix{1.0f};
};