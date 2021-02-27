cmake_minimum_required(VERSION 3.10)

project(nweather)

add_executable(nweather main.cpp)

target_include_directories(nweather PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/cxxops-2.2.1/include"
	"${PROJECT_SOURCE_DIR}/URI"
    )

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json)
add_library(nlohmann INTERFACE)

add_subdirectory(networkclient)
add_subdirectory(weather)
add_subdirectory(HTTPRequest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_link_libraries(nweather PUBLIC HTTPRequest weather networkclient PRIVATE nlohmann)

