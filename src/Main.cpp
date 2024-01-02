#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <variant>
#include <memory>

#include "Const.hpp"
#include "Fractal.hpp"
#include "Render.hpp"

int main(int argc, char *argv[])
{
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  
  // Generate fractal
  std::shared_ptr<Render::Render> render = std::make_shared<Render::Render>();
  double bound = 1.0;
  const int maxIters = 10;
  double resolution = 0.01;
  auto c = Complex(0.0, 0.0);
  auto fractal = Fractal::JuliaSet(bound, c, maxIters);
  auto boundRect = Geometry::ComplexRect(-2.0, 2.0, -2.0, 2.0);
  render->render(fractal, boundRect, resolution);

  // Canvas size
  int width = (boundRect.maxRe() - boundRect.minRe()) / resolution;
  int height = (boundRect.maxIm() - boundRect.minIm()) / resolution;

  // Window size

}