#pragma once

#include <memory>

#include "Geometry.hpp"
#include "Complex.hpp"

namespace Animation
{
  struct Frame
  {
    Geometry::ComplexRect boundRect;
    Z::Z c;
    float resolution;
  };

  class FrameStep
  {
  public:
    virtual Frame next(const Frame &fr) const = 0;
  };

  class ZoomStep : public FrameStep
  {
  public:
    ZoomStep(const float &step) : step(step){};
    float step;
    Frame next(const Frame &fr) const override;
  };

  class ComplexPlaneStep : public FrameStep
  {
  public:
    ComplexPlaneStep(const Z::Z &step) : step(step){};
    Z::Z step;
    Frame next(const Frame &fr) const override;
  };

  struct Params
  {
    Geometry::ComplexRect boundRect;
    std::shared_ptr<FrameStep> frameStep;
    int nFrames;
  };
};