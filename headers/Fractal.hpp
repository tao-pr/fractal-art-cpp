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
    Complex c;
    double bound;
    int nMaxIters;

  public:
    Fractal(const double &bound, const Complex &c, const int nMaxIters) : bound(bound), c(c), nMaxIters(nMaxIters){};
    virtual ~Fractal();
    virtual int convergence(Complex &z, int nIter = 0) const;
  };

  class JuliaSet : public Fractal
  {
  public:
    inline JuliaSet(const double &bound, const Complex &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~JuliaSet(){};
    int convergence(Complex &z, int nIter = 0) const;
  };
}