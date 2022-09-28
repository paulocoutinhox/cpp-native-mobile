cmake_minimum_required(VERSION 3.20.0)
project(native-proj LANGUAGES CXX)

add_library(native-proj "cxx/src/lib.cpp")
set_target_properties(native-proj PROPERTIES PUBLIC_HEADER "cxx/include/lib.hpp")

