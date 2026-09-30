#include <iostream>
#include "../include/Renderer.hpp"
#include "../include/RenderContext.hpp"

void Renderer::render(Renderable &model, Viewable &viewable, Shader &shader)
{
    shader.use();
    shader.setMat4("view", viewable.getViewMatrix());
    shader.setMat4("projection", viewable.getProjectionMatrix());

    RenderContext context{viewable, shader, glm::mat4{1.0f}};

    model.render(context);
}

void Renderer::clear(GLFWwindow *window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
