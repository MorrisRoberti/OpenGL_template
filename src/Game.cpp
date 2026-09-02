#include "../include/Game.hpp"
#include "../assets/2d_shapes/Square.hpp"
#include "../assets/models/Cube.hpp"
#include "../include/Texture.hpp"
#include "../include/Model.hpp"
#include <iostream>
#include <algorithm>

Game::Game()
{
    initWindow();
    setCallbacks();
    initSettings();
    loadShaders();
    initCamera();
}

Game::~Game()
{
    delete shader;
    delete camera;
    delete renderer;
    glfwTerminate();
}

void Game::run()
{

    Model model{"./assets/models/Skull/12140_Skull_v3_L2.obj"};
    model.rotate(glm::vec3{1.0f, 0.f, 0.f}, -90.f);
    model.setScale(glm::vec3{0.1f, 0.1f, 0.1f});

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);

        renderer->render(model, *camera, *shader);

        renderer->clear(window);
    }
}

void Game::draw()
{
}

void Game::update()
{
}

void Game::initWindow()
{

    glfwWindowHint(GLFW_VERSION_MAJOR, 3.3);

    if (!glfwInit())
    {
        std::cerr << "Error while creating the glfwContext" << std::endl;
        exit(1);
    }

    window = glfwCreateWindow(600, 600, "New Game", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Error while creating the glfwWindow" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error while initializing GLEW" << std::endl;
        exit(1);
    }
}

void Game::initCamera()
{
    camera = new Camera{glm::vec3{0.f, 0.f, 10.f}, glm::vec3{0.f}, glm::vec3{0.f, 1.f, 0.f}};
    glm::mat4 transformation = camera->getProjectionMatrix() * camera->getViewMatrix() * glm::mat4(1.0f);
    shader->setMat4("transformation", transformation);
}

void Game::setCallbacks()
{
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
                                   { glViewport(0, 0, width, height); });
}

void Game::initSettings()
{
    glClearColor(0.f, 0.7f, 0.5f, 1.0f);
    // this breaks the render of 2d elements
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glDepthMask(GL_FALSE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);
}

void Game::processInput(float deltaTime)
{

    glfwGetCursorPos(window, &mousePos.x, &mousePos.y);

    angle.x = (mousePos.x - lastMousePos.x) * sensitivity * deltaTime;
    angle.y = (mousePos.y - lastMousePos.y) * sensitivity * deltaTime;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        if (mousePos.x != lastMousePos.x)
            camera->rotate(glm::vec3(0.f, 1.0f, 0.f), angle.x);

        if (mousePos.y != lastMousePos.y)
            camera->rotate(glm::vec3(1.f, 0.0f, 0.f), angle.y);
    }

    lastMousePos.x = mousePos.x;
    lastMousePos.y = mousePos.y;

    float offset = 5.f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->translate(glm::vec3(0.f, 0.f, offset));
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->translate(glm::vec3(0.f, 0.f, -offset));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->translate(glm::vec3(offset, 0.f, 0.f));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->translate(glm::vec3(-offset, 0.f, 0.f));
    }
}

void Game::loadShaders()
{
    shader = new Shader{"/home/morris/Workspace/scrap_workspace/opengl_test/boilerplate/shaders/tex/tex.vert",
                        "/home/morris/Workspace/scrap_workspace/opengl_test/boilerplate/shaders/tex/tex.frag"};
}
