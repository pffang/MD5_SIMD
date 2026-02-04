project(MD5_SIMD_TESTS)

enable_testing()

include(GoogleTest)

include_directories(${MD5_SIMD_SOURCE_DIR}/include ${MD5_SIMD_LIB_SOURCE_DIR}
                    ${MD5_SIMD_SOURCE_DIR}/CPUID/include)

add_executable(UnitTests test.cpp testMD5AVX.cpp testMD5AVX2.cpp testMD5RFC.cpp
                         testMD5SSE.cpp)

target_link_libraries(UnitTests CPUID MD5_SIMD gtest)

gtest_discover_tests(UnitTests)

add_executable(SpeedTest SpeedTest.cpp)
target_link_libraries(SpeedTest CPUID MD5_SIMD crypto)
