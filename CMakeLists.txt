cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

set(DEFAULT_BUILD_TYPE "Release")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(DEFAULT_BUILD_TYPE "Debug")
  add_definitions(-DDEBUG)
endif()

include(FetchContent)

FetchContent_Declare(   
    Catch2 
  	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG devel
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/catch2
)

set("Catch2_DIR" ${CMAKE_SOURCE_DIR}/catch2)

FetchContent_MakeAvailable(Catch2)

project(Tests)

add_executable(
    Tests
    ./test/main_test.cpp
    ./test/test_vec3_int.cpp
)

target_include_directories(
    Tests
    PRIVATE ${Catch2_DIR}/src
    PRIVATE ./src
)

target_link_libraries(
    Tests
    PRIVATE Catch2::Catch2WithMain
)


project(VRG_DEMO)

add_executable(
    VRG_DEMO
    ./src/main.cpp
)

target_include_directories(
    VRG_DEMO
    PRIVATE ./src
)