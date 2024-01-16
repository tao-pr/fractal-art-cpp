#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <variant>
#include <memory>
#include <tuple>
#include <optional>
#include <filesystem>

#include "Const.hpp"
#include "Fractal.hpp"
#include "Render.hpp"
#include "ArgParser.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  // Run params
  std::string sre = argc > 1 ? argv[1] : "0.0";
  std::string sim = argc > 2 ? argv[2] : "0.0";
  std::string iter = argc > 3 ? argv[3] : "25";
  std::string sres = argc > 4 ? argv[4] : "0.001";
  std::string sbound = argc > 5 ? argv[5] : "1.0";
  std::string sfractal = argc > 6 ? argv[6] : "julia";
  std::string scentre = argc > 7 ? argv[7] : "0.0,0.0";
  std::string animator = argc > 8 ? argv[8] : "";
  double re = atof(sre.c_str());
  double im = atof(sim.c_str());
  double bound = atof(sbound.c_str());
  std::tuple<double, double> centre = ArgParser::parseComplex(scentre);
  auto [centreRe, centreIm] = centre;

  std::cout << "Generating fractal '" << sfractal << "'... c = " << re;
  if (im < 0)
    std::cout << " - " << -im << "i" << std::endl;
  else
    std::cout << " + " << im << "i" << std::endl;
  std::cout << "Max iterations: " << iter << std::endl;
  std::cout << "Resolution: " << sres << std::endl;
  std::cout << "Bound: " << bound << std::endl;
  std::cout << "Centre: " << centreRe << ", " << centreIm << std::endl;

  float aspectRatio = (float)WND_WIDTH / (float)WND_HEIGHT;
  std::cout << "Aspect ratio: " << aspectRatio << std::endl;
  auto boundRect = Geometry::makeComplexRect(centreRe, centreIm, bound * aspectRatio, bound);
  auto animParams = (animator.size() > 1) ? std::optional<Animation::Params>(ArgParser::parseAniParams(animator, boundRect)) : std::nullopt;

  if (animParams.has_value())
  {
    std::cout << "Animation: " << animator << std::endl;
    std::cout << "Animation frames: " << animParams->nFrames << std::endl;
  }
  else
    std::cout << RED << "No animation" << RESET << std::endl;

  // Generate fractal
  std::shared_ptr<Render::Render> render = std::make_shared<Render::Render>();
  const int maxIters = atoi(iter.c_str());
  double resolution = atof(sres.c_str());
  auto c = Complex(re, im);

  std::shared_ptr<Fractal::Fractal> fractal;

  if (sfractal == "complex")
    fractal = std::make_shared<Fractal::ComplexJuliaSet>(Fractal::ComplexJuliaSet(bound, c, maxIters));
  else if (sfractal == "degree4")
    fractal = std::make_shared<Fractal::Degree4JuliaSet>(Fractal::Degree4JuliaSet(bound, c, maxIters));
  else if (sfractal == "julia")
    fractal = std::make_shared<Fractal::JuliaSet>(Fractal::JuliaSet(bound, c, maxIters));
  else if (sfractal == "nova")
    fractal = std::make_shared<Fractal::NovaFractal>(Fractal::NovaFractal(bound, c, maxIters));
  else
  {
    std::cout << "Unknown fractal '" << sfractal << "'" << std::endl;
    return -1;
  }

  // Render still image / animation
  if (animParams.has_value())
  {
    // codecs: https://gist.github.com/takuma7/44f9ecb028ff00e2132e
    std::cout << "Rendering animation of " << animParams->nFrames << " frames..." << std::endl;
    cv::VideoWriter video("rendered.mp4", cv::VideoWriter::fourcc('a', 'v', 'c', '1'), FPS, cv::Size(WND_WIDTH, WND_HEIGHT));

    auto frame = Animation::Frame{boundRect, c, resolution};
    for (unsigned int fi = 0; fi < animParams->nFrames; fi++)
    {
      std::cout << CYAN << "Rendering frame #" << fi << RESET << std::endl;
      auto frameImage = render->render(fractal, frame.boundRect, frame.resolution, false);

      if (fi < animParams->nFrames - 1)
      {
        frame = animParams->frameStep->next(frame);
        if (frame.c != c)
        {
          std::cout << "new z = [" << frame.c.re << ", " << frame.c.im << "]" << std::endl;
          fractal->updateC(frame.c);
          c = frame.c;
        }
      }
      else
        break;

      if (fi % animParams->decayItersEvery == 0 && fi > 0)
      {
        // decay number of iteration
        fractal->decayIters(
          animParams->decaySize, 
          animParams->minNumIters,
          animParams->maxNumIters);
        std::cout << YELLOW << "Decaying max iters to " << fractal->maxIters() << RESET << std::endl;
      }

#ifdef RENDER_FRAME_IMAGE
      fs::path root = fs::current_path();
      fs::path framePath = root / "frames/" / ("f-" + std::to_string(fi) + ".png");
      std::cout << "Writing frame to " << framePath << std::endl;
      cv::imwrite(framePath.string(), frameImage);
#endif
      video.write(frameImage);
    }

    video.release();
  }
  else
  {
    std::cout << "Rendering still image..." << std::endl;
    render->render(fractal, boundRect, resolution, true);
  }

  std::cout << "Press any key to exit..." << std::endl;
  cv::waitKey(0);
}