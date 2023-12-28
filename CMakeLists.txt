# NOTE: minimum CMake which supports ARM on MacOS is 3.19
cmake_minimum_required(VERSION 3.27)

# Make linking libraries work on MacOS (Arm64 M1)
# https://stackoverflow.com/a/53635241/4154262
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project("julia" LANGUAGES CXX C) # CXX C
set(TARGET_APP "julia")

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

# Configure LLVM & pkg-config
find_package(LLVM REQUIRED CONFIG)
find_package(PkgConfig REQUIRED)

pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
pkg_check_modules(tbb REQUIRED IMPORTED_TARGET tbb)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

message(STATUS "Found LLVM             : ${LLVM_PACKAGE_VERSION}")
message(STATUS "Including headers from : ${LLVM_INCLUDE_DIRS}")
message(STATUS "Linking libraries from : ${LLVM_LIBRARY_DIRS}")

# Include / Lib dirs
include_directories(
  $ENV{LLVM_INCLUDE_DIR} 
  $ENV{TBB_INCLUDE_DIR}
  $ENV{GL_INCLUDE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)
link_directories(
  $ENV{LLVM_LIB_DIR}
  $ENV{TBB_LIB_DIR}
  $ENV{GL_LIB_DIR}
)

# Source files
# taotodo avoid globbing
message("Including source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCES 
  "${CMAKE_CURRENT_SOURCE_DIR}/headers/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
set(APP_SRC src/Main.cpp)

# Executable
add_executable(${TARGET_APP} ${SOURCES})
set_target_properties(${TARGET_APP} PROPERTIES 
  OUTPUT_NAME "julia"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Link with LLVM libraries & other dependencies
message(STATUS "Linking LLVM libraries: ${llvm_libs}")
target_link_libraries( ${TARGET_APP} ${llvm_libs} -ltbb -lglfw)

message(STATUS "Build output : ${CMAKE_BINARY_DIR}")


