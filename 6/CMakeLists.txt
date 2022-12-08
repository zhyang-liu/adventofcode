cmake_minimum_required(VERSION 3.24)
project(6)

set(CMAKE_CXX_STANDARD 14)

add_executable(6 main.cpp ../common/utils.h ../common/utils.cpp part-1.hpp part-2.hpp)
file(COPY example-1 example-2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/input)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()
