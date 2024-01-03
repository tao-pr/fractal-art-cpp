#pragma once

#include <vector>
#include <iostream>
#include <atomic>
#include <memory>
#include <string>
#include <sstream>
#include <math.h>

// https://github.com/oneapi-src/oneTBB/blob/master/examples/parallel_for_each/parallel_preorder/parallel_preorder.cpp
#include "oneapi/tbb/parallel_for_each.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Fractal.hpp"
#include "Complex.hpp"
#include "Geometry.hpp"
#include "Const.hpp"

namespace Render
{
  class RenderTask
  {
  public:
    int x, y;             // pixel coordinates
    unsigned char *pixel; // pointer to first pixel of 3 (RGB)
    Z::Z z;
    Fractal::Fractal const *fractal;
    int iter;
    RenderTask(const Fractal::Fractal *fractal, const int x, const int y, const Z::Z &z, unsigned char *pixel)
        : fractal(fractal), x(x), y(y), z(z), iter(0), pixel(pixel){};
  };

  class Render
  {
  public:
    void operator()(const RenderTask &t, oneapi::tbb::feeder<RenderTask> &feeder) const
    {
#ifdef DEBUG
      std::stringstream ss;
      ss << "rendering " << t.z.re;
      if (t.z.im < 0)
        ss << " - " << -t.z.im << "i" << std::endl;
      else
        ss << " + " << t.z.im << "i" << std::endl;

      std::cout << ss.str();
#endif

      // Paint pixel with convergence value
      const auto v = t.fractal->convergence(t.z, 0);
      const float ratio = (float)v / (float)t.fractal->maxIters();
      const float highHalfRatio = min(0.25f, ratio - 0.25f) / 0.75f;
      const unsigned char b = floor(255.0f * (1.0f - ratio));
      const unsigned char g = 0;
      const unsigned char r = floor(255.0f * powf(ratio, exp(0.0f)));

      *(t.pixel) = b;
      *(t.pixel + 1) = g;
      *(t.pixel + 2) = r;
    };

    void render(const Fractal::Fractal &fractal, const Geometry::ComplexRect &boundRect, const double &resolution = 0.01)
    {
      std::vector<RenderTask> tasks;

      int width = boundRect.width(resolution);
      int height = boundRect.height(resolution);
      unsigned char *pixels = new unsigned char[width * height * 3];

      for (double r = boundRect.minRe(); r < boundRect.maxRe(); r += resolution)
        for (double i = boundRect.minIm(); i < boundRect.maxIm(); i += resolution)
        {
          int x = floor((r - boundRect.minRe()) / resolution);
          int y = floor((i - boundRect.minIm()) / resolution);

          auto z = Z::Z(r, i);
          tasks.push_back(RenderTask(&fractal, x, y, z, &pixels[x * 3 + (y * width * 3)]));
        }

      // render all in parallel
      std::cout << "Submitting " << tasks.size() << " parallel render tasks (" << width << "x" << height << ")" << std::endl;
      oneapi::tbb::parallel_for_each(tasks.begin(), tasks.end(), Render());

      std::cout << GREEN << "Finished " << tasks.size() << " parallel render tasks (" << width << "x" << height << ")" << RESET << std::endl;

      // Display plot
      auto rendered = cv::Mat(height, width, CV_8UC3, pixels);
      cv::namedWindow("Fractal");
      display(rendered);
    }

    void display(cv::Mat &rendered)
    {
      // Resize to fit window
      if (rendered.size().width != WND_WIDTH || rendered.size().height != WND_HEIGHT)
      {
        cv::Mat resized;
        cv::resize(rendered, resized, cv::Size(WND_WIDTH, WND_HEIGHT));
        cv::imshow("Fractal", resized);
        std::cout << "Resized from " << rendered.size << " to " << WND_WIDTH << " x " << WND_HEIGHT << std::endl;
      }
      else
        cv::imshow("Fractal", rendered);

      cv::imwrite("fractal.png", rendered);
    }

  };

}