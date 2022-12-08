cmake_minimum_required(VERSION 3.24)
project(4)

set(CMAKE_CXX_STANDARD 11)

add_executable(4 main.cpp ../common/utils.cpp ../common/utils.h part-1.hpp)
file(COPY example DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/input)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()