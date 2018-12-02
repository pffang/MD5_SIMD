project(MD5_SIMD_TESTS)

include(GoogleTest)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

include_directories(
	${MD5_SIMD_SOURCE_DIR}/include
	${MD5_SIMD_LIB_SOURCE_DIR}
	${MD5_SIMD_SOURCE_DIR}/CPUID/include
)

add_executable(tests ${SRC_LIST})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(tests CPUID MD5_SIMD gtest Threads::Threads)

enable_testing()
gtest_discover_tests(tests)
#add_custom_command(TARGET tests POST_BUILD COMMAND tests)