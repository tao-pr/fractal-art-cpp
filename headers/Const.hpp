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

// const int WND_WIDTH = 1920;
// const int WND_HEIGHT = 1080;
const int WND_WIDTH = 3840;
const int WND_HEIGHT = 2160;
const int FPS = 24;
