cmake_minimum_required(VERSION 3.10)

project(nweather)

add_executable(nweather main.cpp)

target_include_directories(nweather PUBLIC
	"${PROJECT_BINARY_DIR}"
    )

add_subdirectory(networkclient)
add_subdirectory(weather)
add_subdirectory(HTTPRequest)
add_subdirectory(cxxopts)
add_subdirectory(nlohmann)
add_subdirectory(URI)

# target_link_directories(${PROJECT_NAME} PUBLIC nlohmann/ cxxopts/ URI/ weather/ networkclient/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_link_libraries(nweather cxxopts URI cxxopts nlohmann HTTPRequest weather networkclient)

