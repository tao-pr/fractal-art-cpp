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
    Z::Z c;
    double bound;
    int nMaxIters;

  public:
    Fractal(const double &bound, const Z::Z &c, const int nMaxIters) : bound(bound), c(c), nMaxIters(nMaxIters){};
    virtual ~Fractal();

    // Supposed to be atomic and thread-safe
    virtual int convergence(Z::Z &z, int nIter = 0) const;
  };

  class JuliaSet : public Fractal
  {
  public:
    inline JuliaSet(const double &bound, const Z::Z &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~JuliaSet(){};
    int convergence(Z::Z &z, int nIter = 0) const;
  };
}