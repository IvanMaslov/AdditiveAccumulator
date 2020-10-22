cmake_minimum_required(VERSION 3.14)
project(crypto)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

add_executable(crypto main.cpp fast_tree_v1.cpp merkle_tree.cpp sha256.cpp)