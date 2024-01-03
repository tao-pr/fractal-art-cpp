#pragma once

#include <math.h>

#include "Complex.hpp"

namespace Geometry
{
  class ComplexRect
  {
    double r0;
    double r1;
    double i0;
    double i1;

  public:
    ComplexRect(const double &r0, const double &r1, const double &i0, const double &i1) : r0(r0), r1(r1), i0(i0), i1(i1){};
    bool isInside(const Z::Z &z) const
    {
      return (z.re >= r0 && z.re <= r1 && z.im >= i0 && z.im <= i1);
    };
    double minRe() const { return r0; };
    double maxRe() const { return r1; };
    double minIm() const { return i0; };
    double maxIm() const { return i1; };
    int width(double resolution) const { return ceil((r1 - r0) / resolution); };
    int height(double resolution) const { return ceil((i1 - i0) / resolution); };
  };
};