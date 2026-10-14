#pragma once
#include "./RenderContext.hpp"

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void render(const RenderContext &context) = 0;
};