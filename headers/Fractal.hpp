#pragma once

#include <string>
#include <vector>

#include "Complex.hpp"
#include "Geometry.hpp"

namespace Fractal
{
  class Fractal
  {
  protected:
    Geometry::ComplexRect bound;

  public:
    Fractal(const Geometry::ComplexRect &bound) : bound(bound){};
    virtual ~Fractal();
    virtual int convergence(Complex& z, int nIter=0) const;
  };

  class JuliaSet : public Fractal
  {
    inline ~JuliaSet() {};
    inline int convergence(Complex& z, int nIter=0) const { return -1; };
  };
}