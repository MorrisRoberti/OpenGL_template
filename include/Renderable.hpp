#pragma once
#include <glm/gtc/type_precision.hpp>
#include "./Shader.hpp"
#include "./RenderContext.hpp"

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void render(RenderContext &context) = 0;
};