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
    float oldRange = oldRect.maxRe() - oldRect.minRe();
    float newRange = newRect.maxRe() - newRect.minRe();
    float resolution = newRange * fr.resolution / oldRange;

    std::cout << "[" << newRect.minRe() << ", " << newRect.maxRe() << "] res = " << resolution << std::endl;

    #ifdef DEBUG
    std::cout << "old width = " << oldRect.width(fr.resolution) << std::endl;
    std::cout << "new width = " << newRect.width(fr.resolution) << std::endl;
    std::cout << "new width' = " << newRect.width(resolution) << std::endl;
    #endif

    return Frame{newRect, fr.c, resolution};
  };

  Frame ComplexPlaneStep::next(const Frame &fr) const
  {
    auto c = fr.c + this->step;
    return Frame{fr.boundRect, c, fr.resolution};
  };
};