#pragma once 

#include <vector>
#include <iostream>
#include <atomic>
#include <memory>
#include <string>
#include <sstream>

// https://github.com/oneapi-src/oneTBB/blob/master/examples/parallel_for_each/parallel_preorder/parallel_preorder.cpp
#include "oneapi/tbb/parallel_for_each.h"

#include "Fractal.hpp"
#include "Complex.hpp"
#include "Geometry.hpp"
#include "Const.hpp"

namespace Render 
{
// for (double a=reMin; a<=reMax; a+=resolution)
//     for (double b=imMin; b<=imMax; b+=resolution)
//     {
//       cnt ++;
//       int x = floor((a-reMin)/resolution);
//       int y = floor((b-imMin)/resolution);
//       int percent = floor(100.0f * cnt / (float)tot);
//       auto z = Complex<double>(a,b);
//       const auto v = convergence(z, 0);
//       int _b = 0;
//       int _g = floor(std::min(255.0f, floor(255.0f * powf((this->nMaxIters - v)/20.0f, 2.0f))));
//       int _r = floor(255.0f * (this->nMaxIters - v)/20.0f);
//       auto& px = canvas.at<Vec3b>(Point(y,x));
//       px[2] = _b;
//       px[1] = _g;
//       px[0] = _r;
//     }

  class RenderTask
  {
    public:
      const Fractal::Fractal* fractal;
      Complex z;
      int iter;

      RenderTask(const Fractal::Fractal* fractal, const Complex& z) : fractal(fractal), z(z), iter(0) {};
  };

  class Render 
  {
    public:
      std::vector<unsigned char> canvas {};

      void operator()(const RenderTask& t, oneapi::tbb::feeder<RenderTask> &feeder) const 
      {
        std::stringstream ss;
        ss << "rendering " << t.z.r;
        if (t.z.i < 0) ss << " - " << -t.z.i << "i" << std::endl;
        else ss << " + " << t.z.i << "i" << std::endl;
        
        std::cout << ss.str();

        // taotodo: render me on 2d canvas
      };

      void render(const Fractal::Fractal& fractal, const Geometry::ComplexRect& boundRect, const double& resolution=0.01)
      {
        // Generate vector of points
        // taotodo: perhaps can be faster with coroutine generator
        std::vector<RenderTask> tasks;

        int width = (boundRect.maxRe() - boundRect.minRe()) / resolution;
        int height = (boundRect.maxIm() - boundRect.minIm()) / resolution;
        canvas = std::vector<unsigned char>(width * height * 3);

        for (double r=boundRect.minRe(); r<boundRect.maxRe(); r+=resolution)
          for (double i=boundRect.minIm(); i<boundRect.maxIm(); i+=resolution)
          {
            auto z = Complex(r, i);
            tasks.push_back(RenderTask(&fractal, z));

            // Coordinate for canvas
            int x = floor((r - boundRect.minRe()) / resolution);
            int y = floor((i - boundRect.minIm()) / resolution);

            // Initialise canvas with black pixels
            std::stringstream ss;
            ss << "Initialising pixel (" << x << ", " << y << ") with black." << std::endl;
            std::cout << ss.str();
            canvas[y * x * 3 + 0] = 0;
            canvas[y * x * 3 + 1] = 0;
            canvas[y * x * 3 + 2] = 0;
          }

        // taotodo: render all in parallel
        oneapi::tbb::parallel_for_each(tasks.begin(), tasks.end(), Render());

        std::cout << GREEN << "Submitted " << tasks.size() << " parallel render tasks." << RESET << std::endl;
      }
  };

}