cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(nweather)

add_executable(nweather main.cpp)

target_include_directories(nweather PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/cxxops-2.2.1/include"
	"${PROJECT_SOURCE_DIR}/URI"
    "${PROJECT_SOURCE_DIR}/HTTPRequest"
    )

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json)
add_library(nlohmann INTERFACE)

add_subdirectory(networkclient)
add_subdirectory(weather)

target_link_libraries(nweather PUBLIC weather networkclient PRIVATE nlohmann)

