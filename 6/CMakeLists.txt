CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
PROJECT(6)

SET(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(6 main.cpp ../common/utils.h ../common/utils.cpp part-1.hpp part-2.hpp)
FILE(COPY example-1 example-2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/input)
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF ()
