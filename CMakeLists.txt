cmake_minimum_required(VERSION 3.17)
project(IA_AG_PLE1_2020)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-O2)
add_compile_options(-I)
include_directories(armadillo-10.1.0/include)
add_compile_options(-lopenblas)
add_definitions(-fopenmp)
add_executable(IA_AG_PLE1_2020 main.cpp)