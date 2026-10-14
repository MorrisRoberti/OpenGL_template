#include <GL/glew.h>

#include "Renderable.hpp"

#include "RenderContext.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Viewable.hpp"

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
