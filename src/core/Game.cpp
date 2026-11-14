#include <GL/glew.h>
#include "Game.hpp"

#include "../../assets/shapes/Square.hpp"
#include "Camera.hpp"
#include "graphics/Model.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "utilities/Property.hpp"
#include "utilities/Signal.hpp"
#include "UICamera.hpp"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <vector>

constexpr double initialHp = 100;

class Player
{
public:
  Player() : mHp(initialHp), mHasShot(Signal<bool>()) {}

  Property<double> &getHp()
  {
    return mHp;
  }

  Signal<bool> &hasShot()
  {
    return mHasShot;
  }

private:
  Property<double> mHp;
  Signal<bool> mHasShot;
};

class UI
{
public:
  UI() = default;

  void playShootingAnimation()
  {
    std::cout << "SHOOOOOOOOTING!!" << std::endl;
  }

  void decreaseHp(double newHp)
  {
    std::cout << "AHI, now you have: " << newHp << " HP!" << std::endl;
  }
};

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

  delete mShader;
  delete mCamera;
  delete mUi;
  delete mRenderer;
  glfwTerminate();
}

void Game::run()
{

  Player player;

  std::weak_ptr<UI> weakUI;

  auto ui = std::make_shared<UI>();
  weakUI = ui;
  player.getHp().subscribe([weakUI](double newHp)
                           {
            if(auto pt = weakUI.lock())
            pt->decreaseHp(newHp); });

  Square s{500.f, glm::vec3{1.0f, 0.8f, 0.5f}};
  s.setPosition(glm::vec3{0.f, 0.f, 0.f});

  Model model2{
      "./assets/models/Skull/12140_Skull_v3_L2.obj",
  };
  model2.rotate(glm::vec3{1.0f, 0.f, 0.f}, -90.f);
  model2.scale(glm::vec3{0.01f, 0.01f, 0.01f});
  model2.setPosition(glm::vec3{0.f, 0.f, -50.f});

  glfwSetWindowUserPointer(mWindow, &player);
  glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *window, int button, int action, int mods)
                             {
                                  auto* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
                                    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                                    player->getHp().setValue(player->getHp().getValue() - 10.f); });

  float lastFrame = 0.0f;
  while (!glfwWindowShouldClose(mWindow))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(deltaTime);

    // mRenderer->render(model, *mCamera, *mShader);
    mShader->setUniform1i("hasTexture", 1);
    glEnable(GL_DEPTH_TEST);
    mRenderer->render(model2, *mCamera, *mShader);

    mShader->setUniform1i("hasTexture", 0);
    glDisable(GL_DEPTH_TEST);
    mRenderer->render(s, *mUi, *mShader);

    mRenderer->clear(mWindow);
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

  mWindow = glfwCreateWindow(600, 600, "New Game", nullptr, nullptr);

  if (!mWindow)
  {
    std::cerr << "Error while creating the glfwWindow" << std::endl;
    exit(1);
  }

  glfwMakeContextCurrent(mWindow);

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Error while initializing GLEW" << std::endl;
    exit(1);
  }
}

void Game::initCamera()
{
  mCamera = new Camera{glm::vec3{0.f, 0.f, 10.f}};
  glm::mat4 transformation =
      mCamera->getProjectionMatrix() * mCamera->getViewMatrix() * glm::mat4(1.0f);
  mShader->setMat4("transformation", transformation);

  // mUi
  mUi = new UICamera{0.f, 1920.f, 0.f, 1080.f, -1.0f, 1.0f};
}

void Game::setCallbacks()
{
  glfwSetFramebufferSizeCallback(mWindow,
                                 [](GLFWwindow *mWindow, int width, int height)
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

  glfwGetCursorPos(mWindow, &mMousePos.x, &mMousePos.y);

  mAngle.x = (mMousePos.x - mLastMousePos.x) * mSensitivity * deltaTime;
  mAngle.y = (mMousePos.y - mLastMousePos.y) * mSensitivity * deltaTime;

  if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    // if (mMousePos.x != mLastMousePos.x)
    //   mCamera->rotate(glm::vec3(0.f, 1.0f, 0.f), mAngle.x);

    // if (mMousePos.y != mLastMousePos.y)
    //   mCamera->rotate(glm::vec3(1.f, 0.0f, 0.f), mAngle.y);
  }

  mLastMousePos.x = mMousePos.x;
  mLastMousePos.y = mMousePos.y;

  float offset = 15.f * deltaTime;

  if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
  {
    mCamera->translate(glm::vec3(0.f, 0.f, offset));
  }

  if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
  {
    mCamera->translate(glm::vec3(0.f, 0.f, -offset));
  }

  if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
  {
    mCamera->translate(glm::vec3(offset, 0.f, 0.f));
  }

  if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
  {
    mCamera->translate(glm::vec3(-offset, 0.f, 0.f));
  }
}

void Game::loadShaders()
{
  mShader = new Shader{"./assets/shaders/mixed_cam/mixed_cam.vert",
                       "./assets/shaders/mixed_cam/mixed_cam.frag"};
}
