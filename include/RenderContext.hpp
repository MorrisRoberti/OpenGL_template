#pragma once
#include <glm/mat4x4.hpp>

class Viewable;
class Shader;

struct RenderContext
{
    const Viewable &camera;
    Shader &shader;
    glm::mat4 modelMatrix{1.0f};
};