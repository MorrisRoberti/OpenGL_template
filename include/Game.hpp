#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Shader.hpp"
#include "../include/Camera.hpp"
#include "../include/Renderer.hpp"

class Game
{

public:
    Game();

    ~Game();

    void run();

private:
    void initWindow();
    void initCamera();
    void setCallbacks();
    void initSettings();
    void processInput(float deltaTime);
    void loadShaders();

    void draw();
    void update();

    GLFWwindow *window;
    Camera *camera;
    Shader *shader;
    Renderer *renderer;

    glm::dvec2 mousePos{0., 0};

    glm::vec2 lastMousePos{0.f, 0.f};
    glm::vec2 angle{0.f, 0.f};

    float sensitivity{5.f};
};