cmake_minimum_required(VERSION 3.10.0)

set(C_STANDARD 23)
set(CXX_STANDARD 23)

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-march=native)

project(MD5_SIMD)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
  FIND_PACKAGE_ARGS NAMES GTest)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(CPUID/libs)
add_subdirectory(libs)
add_subdirectory(tests)
