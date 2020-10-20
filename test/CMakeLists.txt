project(Google_tests)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(gtest_run
        test1.cpp
        ../fast_tree_v1.cpp)
target_link_libraries(gtest_run gtest gtest_main)
