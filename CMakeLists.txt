cmake_minimum_required(VERSION 3.20.0)
project(native-proj LANGUAGES CXX)

set(NATIVE_TARGET "" CACHE STRING "Target Name")
message(STATUS "Target: ${NATIVE_TARGET}")

set(SRC_FILES "cxx/src/lib.cpp")
set(INC_FILES "cxx/include/lib.hpp")

if (NATIVE_TARGET STREQUAL "kotlin")
    add_library(native-proj SHARED ${SRC_FILES})
elseif (NATIVE_TARGET STREQUAL "java")
    add_library(native-proj SHARED ${SRC_FILES})
else()
    add_library(native-proj ${SRC_FILES})
endif()

set_target_properties(native-proj PROPERTIES PUBLIC_HEADER ${INC_FILES})
