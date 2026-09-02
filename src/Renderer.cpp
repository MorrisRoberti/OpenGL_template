#include "../include/Renderer.hpp"
#include <iostream>

void Renderer::render(Shape &model, Camera &camera, Shader &shader)
{
    shader.use();
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("projection", camera.getProjectionMatrix());
    shader.setMat4("model", model.getModelMatrix());
    shader.setUniform1i("gSampler", 0);

    glBindVertexArray(model.getVAO());
    glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::render(Model &mesh, Camera &camera, Shader &shader)
{
    shader.use();
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("projection", camera.getProjectionMatrix());
    shader.setMat4("model", mesh.getModelMatrix());
    shader.setUniform1i("gSampler", 0);

    mesh.render();
}

void Renderer::clear(GLFWwindow *window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
