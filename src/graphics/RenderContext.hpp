#pragma once
#include "Shader.hpp"
#include "Viewable.hpp"

#include <glm/mat4x4.hpp>

struct RenderContext
{
    const Viewable &camera;
    Shader &shader;
    glm::mat4 modelMatrix{1.0f};
};