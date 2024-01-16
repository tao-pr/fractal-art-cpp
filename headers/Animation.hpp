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
    double resolution;
  };

  class FrameStep
  {
  public:
    virtual Frame next(const Frame &fr) const = 0;
  };

  class ZoomStep : public FrameStep
  {
  public:
    ZoomStep(const double &ratio) : ratio(ratio){};
    double ratio;
    Frame next(const Frame &fr) const override;
  };

  class ComplexPlaneStep : public FrameStep
  {
  public:
    ComplexPlaneStep(const Z::Z &step) : step(step){};
    Z::Z step;
    Frame next(const Frame &fr) const override;
  };

  class AngularRotationStep : public FrameStep
  {
  public:
    AngularRotationStep(const double &angle) : angle(angle){};
    double angle; // in Radian
    Frame next(const Frame &fr) const override;
  };

  struct Params
  {
    Geometry::ComplexRect boundRect;
    std::shared_ptr<FrameStep> frameStep;
    int nFrames;

    // Decay factors
    int decayItersEvery; // number of steps to decay number of iterations
    int decaySize; // size of iterations to decay
    int minNumIters; // minimum number of iterations after final decay
  };
};