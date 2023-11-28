cmake_minimum_required(VERSION 3.24)
project(projekt_Netsim)

set(CMAKE_CXX_STANDARD 17)

add_executable(projekt_Netsim main.cpp include/package.hpp src/package.cpp src/package.cpp src/storage_types.cpp include/storage_types.hpp include/types.hpp)
