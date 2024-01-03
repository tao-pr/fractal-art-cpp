#pragma once

#include <math.h>
#include <opencv2/core/types.hpp>

using namespace cv;

namespace Z
{
  typedef Complex<double> Z;

  inline Z zero = Z(0,0);

  inline Z sqr(const Z& z)
  {
    return Z(z.re*z.re - z.im*z.im, 2*z.re*z.im);
  }

  inline double mag(const Z &z)
  {
    return sqrt(z.re*z.re + z.im*z.im);
  }
}