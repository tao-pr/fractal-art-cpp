#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <variant>
#include <memory>

#include <GLFW/glfw3.h>

#include "Const.hpp"
#include "Fractal.hpp"
#include "Render.hpp"

GLFWwindow *initGL()
{
  std::cout << "Initialising OpenGL framework ...";
  if (!glfwInit())
  {
    std::cout << RED << "[FAILED]" << RESET << std::endl;
    return nullptr;
  }
  std::cout << GREEN << "[OK]" << RESET << std::endl;

  auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Fractal", NULL, NULL);
  if (!window)
  {
    std::cout << RED << "FAILED to create an OpenGL window." << RESET << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  return window;
}

int main(int argc, char *argv[])
{
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  // Initialise OpenGL
  auto window = initGL();
  if (window == nullptr)
    return -1;

  // Generate fractal
  std::shared_ptr<Render::Render> render = std::make_shared<Render::Render>();
  double bound = 1.0;
  const int maxIters = 10;
  double resolution = 0.1;
  auto c = Complex(0.0, 0.0);
  auto fractal = Fractal::JuliaSet(bound, c, maxIters);
  auto boundRect = Geometry::ComplexRect(-2.0, 2.0, -2.0, 2.0);
  render->render(fractal, boundRect, resolution);

  // Event loop until window is closed
  while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
}