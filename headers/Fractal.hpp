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
    int maxIters() const { return this->nMaxIters; };

    // Supposed to be atomic and thread-safe
    virtual int convergence(const Z::Z &z, int nIter = 0) const = 0;
  };

  class JuliaSet : public Fractal
  {
  public:
    inline JuliaSet(const double &bound, const Z::Z &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~JuliaSet(){};
    int convergence(const Z::Z &z, int nIter = 0) const override;
  };

  class Degree4JuliaSet : public Fractal
  {
  public:
    inline Degree4JuliaSet(const double &bound, const Z::Z &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~Degree4JuliaSet(){};
    int convergence(const Z::Z &z, int nIter = 0) const override;
  };

  class ComplexJuliaSet : public Fractal
  {
  public:
    inline ComplexJuliaSet(const double &bound, const Z::Z &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~ComplexJuliaSet(){};
    int convergence(const Z::Z &z, int nIter = 0) const override;
  };

  class NovaFractal : public Fractal
  {
  public:
    inline NovaFractal(const double &bound, const Z::Z &c, const int nMaxIters) : Fractal(bound, c, nMaxIters){};
    inline ~NovaFractal(){};
    int convergence(const Z::Z &z, int nIter = 0) const override;
  };
}