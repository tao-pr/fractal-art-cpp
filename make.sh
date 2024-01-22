#!/bin/sh

# For cross compilation, we can set DCMAKE_OSX_ARCHITECTURES='arm64;arm7;arm7s' so on

# Run `llvm-config` to get more LLVM configurations

mkdir -p bin
cd bin

export LLVM_LIB_DIR="$(llvm-config --libdir) $(llvm-config --libdir)/c++"
export LLVM_INCLUDE_DIR=$(llvm-config --includedir)/c++/v1
export LLVM_ROOT=$(brew --prefix llvm@16) # for cmakelist

if [ $(uname -m) = "x86_64" ]; then
  ARCH="x86_64"
  TARGET="x86_64"
  echo "Building for Intel x86_64"
else
  ARCH="arm64"
  TARGET="aarch64"
  echo "Building for ARM64"
fi

cmake -DCMAKE_C_COMPILER=$(brew --prefix llvm@16)/bin/clang \
      -DCMAKE_CXX_COMPILER=$(brew --prefix llvm@16)/bin/clang++ \
      -DCMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_OSX_ARCHIECTURES="$ARCH" \
      -DDEFAULT_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_OSX_ARCHITECTURES="$ARCH" \
      -DLLVM_TARGETS_TO_BUILD="$TARGET" \
      -DLLVM_DEFAULT_TARGET_TRIPLE=$(llvm-config --host-target) \
      -DCMAKE_BUILD_TYPE=Release \
      -DLLVM_BUILD_RUNTIME=Off \
      -DLLVM_INCLUDE_TESTS=Off \
      ..
make