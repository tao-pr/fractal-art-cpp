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
  double resolution = 0.01;
  auto c = Complex(0.0, 0.0);
  auto fractal = Fractal::JuliaSet(bound, c, maxIters);
  auto boundRect = Geometry::ComplexRect(-2.0, 2.0, -2.0, 2.0);
  render->render(fractal, boundRect, resolution);

  int width = (boundRect.maxRe() - boundRect.minRe()) / resolution;
  int height = (boundRect.maxIm() - boundRect.minIm()) / resolution;

  // Event loop until window is closed
  while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
  {
    glViewport(0, 0, width, height);

    /* Orthogonal viewport */
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 0, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    /* Render image 2D */
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        GL_RGB, GL_UNSIGNED_BYTE,
        render->canvas.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw quad and set texture coords
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f); // Bottom-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex2f(WINDOW_WIDTH, 0.0f); // Bottom-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT); // Top-right corner
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, WINDOW_HEIGHT); // Top-left corner
    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  // taodebug:
  // display image data
  unsigned int n = 0;
  for (auto pixel : render->canvas)
  {
    if (pixel > 0)
      n += 1;
  }
  std::cout << n << " non-zero pixels" << std::endl;
}