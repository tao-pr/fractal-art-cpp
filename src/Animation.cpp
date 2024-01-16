#include "Animation.hpp"

namespace Animation
{
  Frame ZoomStep::next(const Frame &fr) const
  {
    auto oldRect = fr.boundRect;
    auto boundRe = (oldRect.maxRe() - oldRect.minRe()) / 2;
    auto boundIm = (oldRect.maxIm() - oldRect.minIm()) / 2;
    auto newRect = Geometry::makeComplexRect(
        oldRect.centreRe(),
        oldRect.centreIm(),
        boundRe * ratio,
        boundIm * ratio);

    // After zoom, number of pixels should remain the same
    double oldRange = oldRect.maxRe() - oldRect.minRe();
    double newRange = newRect.maxRe() - newRect.minRe();
    double resolution = newRange * fr.resolution / oldRange;

    std::cout << "bound = " << boundIm << ", res = " << resolution << std::endl;

    return Frame{newRect, fr.c, resolution};
  };

  Frame ComplexPlaneStep::next(const Frame &fr) const
  {
    auto c = fr.c + this->step;
    return Frame{fr.boundRect, c, fr.resolution};
  };

  // https://matthew-brett.github.io/teaching/rotation_2d.html
  Frame AngularRotationStep::next(const Frame &fr) const
  {
    // Rotational angle (delta)
    double cosRot = cos(this->angle);
    double sinRot = sin(this->angle);

    // Rotate by angle
    auto c = Z::Z(cosRot*fr.c.re - sinRot*fr.c.im, sinRot*fr.c.re + cosRot*fr.c.im);
    return Frame{fr.boundRect, c, fr.resolution};
  };
};