#pragma once

#include <math.h>
#include <opencv2/core/types.hpp>

// class Complex
// {
// public:
//   double r;
//   double i;
//   Complex(const double &r, const double &i) : r(r), i(i){};
//   ~Complex(){};
//   double l2norm() const { return sqrt(r * r + i * i); };
//   Complex square() const
//   {
//     return Complex(r * r - i * i, 2 * r * i);
//   };

//   Complex operator+(const Complex &z) const
//   {
//     return Complex(r + z.r, i + z.i);
//   };
// };

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