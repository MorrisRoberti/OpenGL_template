#include <GL/glew.h>
#include "../include/Game.hpp"

#include <vector>
#include <iostream>
#include <glm/mat4x4.hpp>

#include "../include/Camera.hpp"
#include "../include/UICamera.hpp"
#include "../include/Renderer.hpp"
#include "../include/Shader.hpp"
#include "../assets/2d_shapes/Square.hpp"
#include "../include/Model.hpp"
#include "../include/Texture.hpp"

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

std::vector<glm::mat4> genMat(int n)
{
  std::vector<glm::mat4> modelMatrices(n, glm::mat4{1.0f});

  modelMatrices[0] = glm::rotate(modelMatrices[0], glm::radians(-90.f),
                                 glm::vec3{1.0f, 0.f, 0.f});
  modelMatrices[0] = glm::scale(modelMatrices[0], glm::vec3{0.1f, 0.1f, 0.1f});

  for (int i = 1; i < n; ++i)
  {
    modelMatrices[i] =
        glm::translate(modelMatrices[i], glm::vec3{i * 2.0f, 0.f, 0.f});
    modelMatrices[i] = glm::rotate(modelMatrices[i], glm::radians(-90.f),
                                   glm::vec3{1.0f, 0.f, 0.f});
    modelMatrices[i] =
        glm::scale(modelMatrices[i], glm::vec3{0.1f, 0.1f, 0.1f});
  }

  return modelMatrices;
}

void Game::run()
{

  // auto v = genMat(100);
  // auto v2 = v;
  // Model model{
  //     "./assets/models/Skull/12140_Skull_v3_L2.obj",
  // };
  // model.rotate(glm::vec3{1.0f, 0.f, 0.f}, -90.f);
  // model.scale(glm::vec3{0.01f, 0.01f, 0.01f});

  Square s{500.f, glm::vec3{1.0f, 0.8f, 0.5f}};
  s.setPosition(glm::vec3{0.f, 0.f, 0.f});

  Model model2{
      "./assets/models/Skull/12140_Skull_v3_L2.obj",
  };
  model2.rotate(glm::vec3{1.0f, 0.f, 0.f}, -90.f);
  model2.scale(glm::vec3{0.01f, 0.01f, 0.01f});
  model2.setPosition(glm::vec3{0.f, 0.f, -50.f});

  float lastFrame = 0.0f;
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(deltaTime);

    // renderer->render(model, *camera, *shader);
    shader->setUniform1i("hasTexture", 1);
    glEnable(GL_DEPTH_TEST);
    renderer->render(model2, *camera, *shader);

    shader->setUniform1i("hasTexture", 0);
    glDisable(GL_DEPTH_TEST);
    renderer->render(s, *ui, *shader);

    renderer->clear(window);
  }
}

void Game::draw() {}

void Game::update() {}

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
  camera = new Camera{glm::vec3{0.f, 0.f, 10.f}};
  glm::mat4 transformation =
      camera->getProjectionMatrix() * camera->getViewMatrix() * glm::mat4(1.0f);
  shader->setMat4("transformation", transformation);

  // ui
  ui = new UICamera{0.f, 1920.f, 0.f, 1080.f, -1.0f, 1.0f};
}

void Game::setCallbacks()
{
  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *window, int width, int height)
                                 {
                                   glViewport(0, 0, width, height);
                                 });
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

  float offset = 15.f * deltaTime;

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
  shader = new Shader{"./shaders/mixed_cam/mixed_cam.vert",
                      "./shaders/mixed_cam/mixed_cam.frag"};
}
