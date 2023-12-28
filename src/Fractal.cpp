#include "Fractal.hpp"

namespace Fractal
{
  Fractal::~Fractal() {};
  int Fractal::convergence(Complex &z, int nIter) const
  {
    return -1;
  }

  int JuliaSet::convergence(Complex &z, int nIter) const
  {
    Complex z_ = z.square() + this->c;
    if (z_.l2norm() <= this->bound)
    {
      if (nIter + 1 < this->nMaxIters)
        return convergence(z_, nIter+1);
      else 
        return nIter+1;
    }
    else return nIter;
  }
}