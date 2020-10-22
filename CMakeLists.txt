cmake_minimum_required(VERSION 3.13)
project(crypto)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

add_executable(crypto
        main.cpp
        additive_accumulator_1.cpp
        additive_accumulator_2.cpp
        merkle_tree.cpp
        sha256.cpp
        utils.cpp)