#pragma once

#include <string>

const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[0;32m";
const std::string MAGENTA = "\033[0;35m";
const std::string CYAN = "\033[0;36m";
const std::string YELLOW = "\033[0;33m";
const std::string RESET = "\033[0m";
const std::string NL = "\n"; // Use this instead of std::endl to avoid flushing the buffer

const int WND_WIDTH = 1920;
const int WND_HEIGHT = 1080;
const int FPS = 24;

// #define DECAY_ON
// const int DECAY_ITER_EVERY = 25; // Number of steps to decay iterations 
// const int DECAY_ITERS = -5; // Number of iterations to decay by
// const int MIN_NUM_ITERS = 10;
