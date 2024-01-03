#!/bin/sh

# For cross compilation, we can set DCMAKE_OSX_ARCHITECTURES='arm64;arm7;arm7s' so on

# Run `llvm-config` to get more LLVM configurations

mkdir -p bin
cd bin

export LLVM_LIB_DIR="$(llvm-config --libdir) $(llvm-config --libdir)/c++"
export LLVM_INCLUDE_DIR=$(llvm-config --includedir)/c++/v1
export LLVM_ROOT=$(brew --prefix llvm@16) # for cmakelist

# taotodo make this compatible with both arm64 and x86_64

cmake -DCMAKE_C_COMPILER=$(brew --prefix llvm@16)/bin/clang \
      -DCMAKE_CXX_COMPILER=$(brew --prefix llvm@16)/bin/clang++ \
      -DCMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_OSX_ARCHIECTURES='arm64' \
      -DDEFAULT_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_OSX_ARCHITECTURES='arm64' \
      -DLLVM_TARGETS_TO_BUILD='aarch64' \
      -DLLVM_DEFAULT_TARGET_TRIPLE=$(llvm-config --host-target) \
      -DCMAKE_BUILD_TYPE=Release \
      -DLLVM_BUILD_RUNTIME=Off \
      -DLLVM_INCLUDE_TESTS=Off \
      ..
make