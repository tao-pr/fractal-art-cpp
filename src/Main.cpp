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

  // Run params
  std::string sre = argc > 1 ? argv[1] : "0.0";
  std::string sim = argc > 2 ? argv[2] : "0.0";
  std::string iter = argc > 3 ? argv[3] : "25";
  std::string sres = argc > 4 ? argv[4] : "0.001";
  std::string sbound = argc > 5 ? argv[5] : "1.0";
  float re = atof(sre.c_str());
  float im = atof(sim.c_str());
  float bound = atof(sbound.c_str());

  std::cout << "Generating fractal... c = " << re;
  if (im < 0)
    std::cout << " - " << -im << "i" << std::endl;
  else
    std::cout << " + " << im << "i" << std::endl;
  std::cout << "Max iterations: " << iter << std::endl;
  std::cout << "Resolution: " << sres << std::endl;
  std::cout << "Bound: " << bound << std::endl;
  
  // Generate fractal
  std::shared_ptr<Render::Render> render = std::make_shared<Render::Render>();
  const int maxIters = atoi(iter.c_str());
  double resolution = atof(sres.c_str());
  auto c = Complex(re, im);
  auto fractal = Fractal::JuliaSet(bound, c, maxIters);
  auto boundRect = Geometry::ComplexRect(-bound, bound, -bound, bound);
  render->render(fractal, boundRect, resolution);

  std::cout << "Press any key to exit..." << std::endl;
  cv::waitKey(0);
}