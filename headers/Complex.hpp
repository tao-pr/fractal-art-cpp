#pragma once

#include <math.h>

class Complex
{
public:
  double r;
  double i;
  Complex(const double &r, const double &i) : r(r), i(i){};
  ~Complex(){};
  double l2norm() const { return sqrt(r * r + i * i); };
};