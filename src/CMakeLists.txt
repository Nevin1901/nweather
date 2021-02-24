cmake_minimum_required(VERSION 3.10)

project(nweather)

add_executable(nweather, main.cpp)

target_include_directories(nweather PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/cxxopts" "${PROJECT_SOURCE_DIR}/nlohmann")

configure_file(URI.h URI.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(NetworkClient networkClient.cpp)
add_library(Weather weather.cpp)
add_library(HTTPRequest HTTPRequest.hpp)
add_library

