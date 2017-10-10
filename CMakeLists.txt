cmake_minimum_required(VERSION 3.8)
project(wiki_stats_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    utf8.cpp
    utf8.hpp
    wiki_graph.cpp
    wiki_graph.hpp
    wiki_small.txt
    wiki_stats.cpp)

add_executable(wiki_stats_cpp ${SOURCE_FILES})