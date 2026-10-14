#pragma once
#include <glm/mat4x4.hpp>
#include "./Viewable.hpp"
#include "./Shader.hpp"

struct RenderContext
{
    const Viewable &camera;
    Shader &shader;
    glm::mat4 modelMatrix{1.0f};
};