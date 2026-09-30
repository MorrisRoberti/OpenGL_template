#pragma once
#include "../include/Viewable.hpp"
#include "../include/Shader.hpp"
#include <GLFW/glfw3.h>
#include "../include/Renderable.hpp"

class Renderer
{
public:
    Renderer() = default;

    void render(Renderable &model, Viewable &viewable, Shader &shader);

    void clear(GLFWwindow *window);

private:
};