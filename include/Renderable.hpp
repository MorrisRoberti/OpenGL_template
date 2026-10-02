#pragma once

struct RenderContext;

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void render(const RenderContext &context) = 0;
};