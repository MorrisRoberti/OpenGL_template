#pragma once
#include <glm/gtc/type_precision.hpp>
#include "./Camera.hpp"
#include "./Shader.hpp"

struct RenderContext
{
    const Camera &camera;
    Shader &shader;
    glm::mat4 modelMatrix{1.0f};
};