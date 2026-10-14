#include <GL/glew.h>

#include "../include/Renderable.hpp"

#include "../include/RenderContext.hpp"
#include "../include/Renderer.hpp"
#include "../include/Shader.hpp"
#include "../include/Viewable.hpp"

#include <GLFW/glfw3.h>

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
