#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <sstream>
#include <memory>

#include "Animation.hpp"

namespace ArgParser
{
  /**
   * @brief parse a string to a tuple of double (comma delimited)
   */
  std::tuple<double, double> parseComplex(const std::string &s)
  {
    std::vector<double> values;
    std::stringstream ss(s);
    std::string token;

    while (std::getline(ss, token, ','))
    {
      values.push_back(std::stod(token));
      if (values.size() > 2)
      {
        throw std::runtime_error("Tuple must have 2 floating-point values delimited by a comma");
      }
    }

    return std::make_tuple(values[0], values[1]);
  }

  /**
   * @brief parse a string to animation params
   */
  Animation::Params parseAniParams(const std::string &s, Geometry::ComplexRect &boundRect)
  {
    // Format of the animation params
    //
    // {animationType}:{numFrames}:{params=value},{params=value}

    std::stringstream ss(s);
    std::string aniType;
    std::string token;
    std::string params;

    if (std::getline(ss, aniType, ':'))
    {
      if (!std::getline(ss, token, ':'))
      {
        std::cerr << "Missing animation number of frames" << std::endl;
        throw new std::runtime_error("Missing animation number of frames");
      }

      std::getline(ss, params, ':');
      auto streamParams = std::stringstream(params);

      int numFrames = std::stoi(token);
      if (aniType == "zoom" && params.size() > 1)
      {
        // eg params = "step=0.001,"
        //    params = "step=0.001,foo=bar"
        auto step = std::make_shared<Animation::ZoomStep>(0.001f);

        std::string pair;
        while (std::getline(streamParams, pair, ','))
        {
          std::stringstream pairStream(pair);
          std::string key, value;
          if (std::getline(pairStream, key, '=') && std::getline(pairStream, value, '='))
          {
            std::cout << "extracted: " << key << " -> " << value << std::endl;
            if (key == "step")
            {
              step->step = std::stof(value);
            }
          }
        };

        return Animation::Params{boundRect, step, numFrames};
      }
      else if (aniType == "complex")
      {
        // taotodo:
        throw new std::runtime_error("'Complex' animation type not implemented yet");
      }
    }
    else
    {
      std::cerr << "Animation params must be delimited by a colon" << std::endl;
      throw new std::runtime_error("Animation params must be delimited by a colon");
    }
  }
};