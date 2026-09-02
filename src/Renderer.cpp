#include <iostream>
#include "../include/Renderer.hpp"
#include "../include/RenderContext.hpp"

void Renderer::render(Renderable &model, Camera &camera, Shader &shader)
{
    shader.use();
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("projection", camera.getProjectionMatrix());

    RenderContext context{camera, shader, glm::mat4{1.0f}};

    model.render(context);
}

void Renderer::clear(GLFWwindow *window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
