cmake_minimum_required(VERSION 3.10.0)

set(C_STANDARD 11)
set(CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -march=native -fPIC")

project(MD5_SIMD)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(CPUID/libs)
add_subdirectory(libs)
add_subdirectory(tests)

enable_testing()