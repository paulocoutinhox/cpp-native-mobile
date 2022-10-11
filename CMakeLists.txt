cmake_minimum_required(VERSION 3.20.0)
project(native-proj LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(NATIVE_TARGET "" CACHE STRING "Target Name")
message(STATUS "Target: ${NATIVE_TARGET}")

set(LIB_SRC_FILES "cxx/src/lib.cpp")
set(LIB_INC_FILES "cxx/include/lib.hpp" "cxx/include/type-wrapper.hpp")

set(APP_SRC_FILES "cxx/src/main.cpp")
set(APP_INC_FILES "")

if (NATIVE_TARGET STREQUAL "kotlin")
    add_library(native-proj SHARED ${LIB_SRC_FILES})
    set_target_properties(native-proj PROPERTIES PUBLIC_HEADER ${LIB_INC_FILES})
elseif (NATIVE_TARGET STREQUAL "java")
    add_library(native-proj SHARED ${LIB_SRC_FILES})
    set_target_properties(native-proj PROPERTIES PUBLIC_HEADER ${LIB_INC_FILES})
else()
    add_executable(native-proj ${APP_SRC_FILES})
    #set_target_properties(native-proj PROPERTIES PUBLIC_HEADER ${APP_INC_FILES})
endif()

target_include_directories(native-proj PRIVATE cxx/include)

# dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.2")

# add dependencies to target
target_link_libraries(native-proj nlohmann_json::nlohmann_json)
