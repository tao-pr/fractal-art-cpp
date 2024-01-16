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
    std::shared_ptr<Fractal::Fractal> fractal;
    int iter;
    RenderTask(std::shared_ptr<Fractal::Fractal> fractal, const int x, const int y, const Z::Z &z, unsigned char *pixel)
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
      const unsigned char b = floor(255.0f * (1.0f - ratio));
      const unsigned char g = 0;
      const unsigned char r = floor(255.0f * powf(ratio, exp(0.0f)));

      *(t.pixel) = b;
      *(t.pixel + 1) = g;
      *(t.pixel + 2) = r;
    };

    Mat render(
        std::shared_ptr<Fractal::Fractal> fractal,
        const Geometry::ComplexRect &boundRect,
        const double &resolution = 0.01,
        bool writeToPNG = true)
    {
      std::vector<RenderTask> tasks;

      int width = boundRect.width(resolution);
      int height = boundRect.height(resolution);
      unsigned char *pixels = new unsigned char[width * height * 3];

      std::cout << "Preparing parallel tasks..." << std::endl;
      for (double r = boundRect.minRe(); r < boundRect.maxRe(); r += resolution)
        for (double i = boundRect.minIm(); i < boundRect.maxIm(); i += resolution)
        {
          int x = floor((r - boundRect.minRe()) / resolution);
          int y = floor((i - boundRect.minIm()) / resolution);

          auto z = Z::Z(r, i);
          tasks.push_back(RenderTask(fractal, x, y, z, &pixels[x * 3 + (y * width * 3)]));
        }

      // render all in parallel
      std::cout << "Submitted " << tasks.size() << " parallel render tasks (" << width << "x" << height << ")" << std::endl;
      oneapi::tbb::parallel_for_each(tasks.begin(), tasks.end(), Render());

      std::cout << GREEN << "Finished " << tasks.size() << " parallel render tasks (" << width << "x" << height << ")" << RESET << std::endl;

      // Display plot
      auto rendered = cv::Mat(height, width, CV_8UC3, pixels);
      cv::namedWindow("Fractal");
      return display(rendered, boundRect, writeToPNG);
    }

    Mat display(cv::Mat &rendered, const Geometry::ComplexRect &boundRect, bool writeToPNG = true)
    {
      // Resize to fit window
      cv::Mat resized;
      if (rendered.size().width != WND_WIDTH || rendered.size().height != WND_HEIGHT)
      {
        cv::resize(rendered, resized, cv::Size(WND_WIDTH, WND_HEIGHT));
        cv::imshow("Fractal", resized);
        std::cout << "Resized from " << rendered.size().width << " x " << rendered.size().height << " to " << WND_WIDTH << " x " << WND_HEIGHT << std::endl;
      }
      else
      {
        cv::imshow("Fractal", rendered);
        resized = rendered;
      }

      if (writeToPNG)
        cv::imwrite("fractal.png", rendered);
      Geometry::ComplexRect *boundRectPtr = new Geometry::ComplexRect(boundRect);
      cv::setMouseCallback("Fractal", mouseCallback, boundRectPtr);

      return resized;
    }

    static void mouseCallback(int event, int x, int y, int flags, void *userdata)
    {
      if (event == cv::EVENT_LBUTTONDOWN)
      {
        auto boundRect = (Geometry::ComplexRect *)userdata;
        double re = boundRect->minRe() + (x * (boundRect->maxRe() - boundRect->minRe()) / WND_WIDTH);
        double im = boundRect->minIm() + (y * (boundRect->maxIm() - boundRect->minIm()) / WND_HEIGHT);
        std::cout << "Mouse clicked at (" << re << ", " << im << ")" << std::endl;
      }
    }
  };

}