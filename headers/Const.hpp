#pragma once

#include <string>

const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[0;32m";
const std::string MAGENTA = "\033[0;35m";
const std::string RESET = "\033[0m";
const std::string NL = "\n"; // Use this instead of std::endl to avoid flushing the buffer

const int WND_WIDTH = 2500;
const int WND_HEIGHT = 2500;