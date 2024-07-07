cmake_minimum_required(VERSION 3.16)
project(gdeflate)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gdeflate
add_library(${PROJECT_NAME} STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/GDeflate.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/GDeflateConfig.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/GDeflateCompress.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/GDeflateDecompress.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/TileStream.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.h")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# libgdeflate
add_library(lib${PROJECT_NAME} STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/adler32.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/crc32.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/deflate_compress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/deflate_decompress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gdeflate_compress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gdeflate_decompress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gzip_compress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gzip_decompress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/utils.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/zlib_compress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/zlib_decompress.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/cpu_features.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/adler32_vec_template.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/bt_matchfinder.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/crc32_table.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/crc32_vec_template.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/decompress_template.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gdeflate_decompress_template.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/deflate_compress.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/deflate_constants.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/gzip_constants.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/hc_matchfinder.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/lib_common.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/matchfinder_common.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/unaligned.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/zlib_constants.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/adler32_impl.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/cpu_features.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/crc32_impl.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/crc32_pclmul_template.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/decompress_impl.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/lib/x86/matchfinder_impl.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate/libdeflate.h")
target_include_directories(lib${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate")
if(MSVC)
    # The follow warnings have been disabled to be able to compile this library without making modifications
    # to the original source.
    #  C4244 'return': conversion from 'uint64_t' to 'unsigned int', possible loss of data - compiler_msc.h 68
    #  C4127 conditional expression is constant - common_defs.h 290
    #  C4267 'function': conversion from 'size_t' to 'uint32_t', possible loss of data - common_defs.h  291
    #  C4100 'c': unreferenced formal parameter - deflate_compress.c    2428
    #  C4245 '=': conversion from 'int' to 'unsigned int', signed/unsigned mismatch  - deflate_decompress.c 752
    #  C4456 declaration of 'len' hides previous local declaration - deflate_compress.c 1118
    #  C4018 '>=': signed/unsigned mismatch - decompress_template.h 297
    #  C4146 unary minus operator applied to unsigned type, result still unsigned - bt_matchfinder.h    219
    #  C4310 cast truncates constant value - bt_matchfinder.h   219
    target_compile_options(lib${PROJECT_NAME} PRIVATE /wd4244 /wd4127 /wd4267 /wd4100 /wd4245 /wd4456 /wd4018 /wd4146 /wd4310)
endif()

# connect it up
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ext/libgdeflate")
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME})
