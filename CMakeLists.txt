project(cxxcompat)

macro(ensure_out_of_source_build)
    string(COMPARE EQUAL "${${PROJECT_NAME}_SOURCE_DIR}" "${${PROJECT_NAME}_BINARY_DIR}" insource)
    if(insource)
        message(FATAL_ERROR "You should build in an empty directory.\n(and rm -Rf CMakeCache.txt CMakeFiles)")
    endif(insource)
endmacro(ensure_out_of_source_build)

ensure_out_of_source_build()

cmake_minimum_required(VERSION 2.8)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++1y -Wall -Wextra -I${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(test_type_traits tests/test_type_traits.cxx)
add_executable(test_optional tests/test_optional.cxx)
add_executable(test_memory tests/test_memory.cxx)
add_executable(test_override tests/test_override.cxx)

add_test(test_type_traits test_type_traits)
add_test(test_optional test_optional)
add_test(test_memory test_memory)
add_test(test_override test_override)
