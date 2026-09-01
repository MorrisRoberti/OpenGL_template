#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../assets/meshes/Cube.hpp"
#include "../include/Camera.hpp"
#include "../include/Shader.hpp"
#include "../include/Shape.hpp"
#include "../include/Mesh.hpp"

class Renderer
{
public:
    Renderer() = default;

    void render(Shape &model, Camera &camera, Shader &shader);
    void render(Mesh &mesh, Camera &camera, Shader &shader);

    void clear(GLFWwindow *window);

private:
};