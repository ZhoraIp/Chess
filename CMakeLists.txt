cmake_minimum_required(VERSION 3.20)
project(chess)

set(CMAKE_CXX_STANDARD 14)

#add_executable(chess main.cpp game.cpp helper.cpp view/view.cpp pieces.cpp)

add_executable(chess main.cpp view/view.cpp)
add_library(game game.cpp helper.cpp Pieces/pieces.cpp)
target_link_libraries(chess PRIVATE game)

add_library(my_vector Vector/my_vector.h Vector/my_vector.cpp)

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
add_executable(test gtest.cpp)
target_link_libraries(test PRIVATE game gtest)

