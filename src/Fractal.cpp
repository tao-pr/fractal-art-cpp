#include "Fractal.hpp"

namespace Fractal
{
  Fractal::~Fractal(){};

  int JuliaSet::convergence(const Z::Z &z, int nIter) const
  {
    Complex z_ = Z::sqr(z) + this->c;
    if (Z::mag(z_) <= this->bound)
    {
      if (nIter + 1 < this->nMaxIters)
        return convergence(z_, nIter + 1);
      else
        return nIter + 1;
    }
    else
      return nIter;
  }

  int ComplexJuliaSet::convergence(const Z::Z &z, int nIter) const
  {
    Complex z2 = Z::sqr(z);
    Complex z3 = z2 * z;
    Complex z4 = z3 * z;

    Complex z_ = z4 + (z3 / Z::add(z, -1)) + (z2 / (z3 + Z::add(Z::mul(z2, 4), 5))) + this->c;
    if (Z::mag(z_) <= this->bound)
    {
      if (nIter + 1 < this->nMaxIters)
        return convergence(z_, nIter + 1);
      else
        return nIter + 1;
    }
    else
      return nIter;
  }

  int Degree4JuliaSet::convergence(const Z::Z &z, int nIter) const
  {
    Complex z_ = Z::sqr(Z::sqr(z)) + this->c;
    if (Z::mag(z_) <= this->bound)
    {
      if (nIter + 1 < this->nMaxIters)
        return convergence(z_, nIter + 1);
      else
        return nIter + 1;
    }
    else
      return nIter;
  }
}