#include "Fractal.hpp"

namespace Fractal
{
  Fractal::~Fractal() {};
  int Fractal::convergence(Z::Z &z, int nIter) const
  {
    return -1;
  }

  int JuliaSet::convergence(Z::Z &z, int nIter) const
  {
    Complex z_ = Z::sqr(z) + this->c;
    if (Z::mag(z_) <= this->bound)
    {
      if (nIter + 1 < this->nMaxIters)
        return convergence(z_, nIter+1);
      else 
        return nIter+1;
    }
    else return nIter;
  }
}