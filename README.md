# Fractal Art Render

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/tao-pr/julia-set-cpp/blob/main/LICENSE)

A C++ implementation of Fractal art rendering.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project is a C++ implementation of Julia Set and other fractal seet rendering with OpenGL. One example is Julia Set which is a fractal defined by a complex quadratic polynomial. This program allows you to generate and visualize Julia Set images.

## Features

- Generate high-resolution Julia Set images
- Customize the parameters of the Julia Set
- Save the rendered images to disk

## Getting Started

To get started with Julia Set Render, follow these steps:

1. Clone the repository:

  ```shell
  git clone https://github.com/tao-pr/fractal-art-render.git
  ```

2. Install and configure prerequisites

- Latest XCode Commandline Tools
- CMake
- [LLVM Compiler](https://github.com/llvm/llvm-project/tree/main)
- [TBB](https://github.com/oneapi-src/oneTBB)

For MacOS users, simply run the following

```sh
# Install XCode commandline update (requires a restart)
softwareupdate --list  # list the available update for XCode Commandline Tools
softwareupdate -i <label> # install the available update (specify the label got from previous command)

# Install LLVM
brew install llvm@16
# then follow an instruction on `brew info llvm@16` to bootstrap your environment

# Install TBB
brew install tbb

# Install OpenGL
brew install glfw
```

3. Build the project using clang (LLVM):

  ```shell
  ./make.sh
  ```

4. Run the executable:

  ```shell
  bin/julia
  ```

## Usage

TBD

## Contributing

Contributions are welcome! If you have any ideas, suggestions, or bug reports, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
