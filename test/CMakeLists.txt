project(Google_tests)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(gtest_run
        test1.cpp
        test2.cpp
        ../additive_accumulator_1.cpp
        ../additive_accumulator_2.cpp
        ../sha256.cpp
        ../merkle_tree.cpp
        ../utils.cpp)
target_link_libraries(gtest_run gtest gtest_main)
