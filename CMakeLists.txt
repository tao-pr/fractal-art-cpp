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

pkg_check_modules(TBB REQUIRED IMPORTED_TARGET tbb)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv4)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-stdlib=libc++ -Wall -g -O1")

message(STATUS "Found LLVM             : ${LLVM_PACKAGE_VERSION}")
message(STATUS "Including headers from : ${LLVM_INCLUDE_DIRS}")
message(STATUS "Linking libraries from : ${LLVM_LIBRARY_DIRS}")
message(STATUS "Including TBB from     : ${TBB_INCLUDEDIR} (version ${TBB_VERSION})")
message(STATUS "Including OpenCV from  : ${OPENCV_INCLUDEDIR} (version ${OPENCV_VERSION})")

# Include / Lib dirs
include_directories(
  $ENV{LLVM_INCLUDE_DIRS} 
  ${TBB_INCLUDEDIR}
  ${OPENCV_INCLUDEDIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)
link_directories(
  $ENV{LLVM_LIBRARY_DIRS}
  ${TBB_LIBDIR}
  ${OPENCV_LIBDIR}
)

# Source files
# NOTE: In fact we should avoid GLOBBING source files, but it's just a small project.
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
target_link_libraries(
  ${TARGET_APP} 
  ${llvm_libs} 
  -ltbb 
  -lopencv_photo -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_video)

message(STATUS "Build output : ${CMAKE_BINARY_DIR}")


