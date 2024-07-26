cmake_minimum_required(VERSION 3.20)
project(VRG_DEMO)

set(CMAKE_CXX_STANDARD 20)

set(DEFAULT_BUILD_TYPE "Release")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(DEFAULT_BUILD_TYPE "Debug")
  add_definitions(-DDEBUG)
endif()

add_executable(
    VRG_DEMO
    ./src/main.cpp
)

target_include_directories(
    VRG_DEMO
    PRIVATE ./src
)
