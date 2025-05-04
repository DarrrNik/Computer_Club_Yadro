cmake_minimum_required(VERSION 3.31.3)
project(Computer_Club VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${CMAKE_SOURCE_DIR}/include/")
file(GLOB files "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(main ${files})
