project(MD5_SIMD_LIB)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

add_library(MD5_SIMD STATIC ${SRC_LIST})
