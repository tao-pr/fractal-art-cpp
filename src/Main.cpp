#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <unordered_map>
#include <variant>

#include <GLFW/glfw3.h>

#include "Const.hpp"

int main(int argc, char *argv[])
{
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  // Initialise OpenGL
  std::cout << "Initialising OpenGL framework ...";
  if (!glfwInit())
  {
    std::cout << RED << "[FAILED]" << RESET << std::endl;
    return -1;
  }
  std::cout << GREEN << "[OK]" << RESET << std::endl;
}