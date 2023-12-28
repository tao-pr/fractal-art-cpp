#pragma once

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
    bool isInside(const Complex &z) const
    {
      return (z.r >= r0 && z.r <= r1 && z.i >= i0 && z.i <= i1);
    };
  };
};