#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../assets/models/Cube.hpp"
#include "../include/Camera.hpp"
#include "../include/Shader.hpp"
#include "../include/Shape.hpp"
#include "../include/Model.hpp"

class Renderer
{
public:
    Renderer() = default;

    void render(Shape &model, Camera &camera, Shader &shader);
    void render(Model &mesh, Camera &camera, Shader &shader);

    void clear(GLFWwindow *window);

private:
};