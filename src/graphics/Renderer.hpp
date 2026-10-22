#pragma once
#include <GLFW/glfw3.h>

class Renderable;
class Viewable;
class Shader;

class Renderer
{
public:
    Renderer() = default;

    void render(Renderable &model, Viewable &viewable, Shader &shader);

    void clear(GLFWwindow *window);
};