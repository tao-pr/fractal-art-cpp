#include "Animation.hpp"

namespace Animation
{
  Frame ZoomStep::next(const Frame &fr) const
  {
    auto rect = fr.boundRect;
    auto bound = rect.maxRe() - rect.minRe();
    auto newRect = Geometry::makeComplexRect(
        rect.centreRe(),
        rect.centreIm(),
        bound - step); // zoom in by default
    float resolution = fr.resolution * (bound - step) / bound;
    return Frame{newRect, fr.c, resolution};
  };

  Frame ComplexPlaneStep::next(const Frame &fr) const
  {
    auto c = fr.c + this->step;
    return Frame{fr.boundRect, c, fr.resolution};
  };
};