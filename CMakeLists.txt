cmake_minimum_required(VERSION 3.17)
project(Containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Containers
        iterators.hpp
        main.cpp
        vector.cpp
        vector.hpp enable_if.hpp is_integral.hpp map.hpp pair.hpp)
