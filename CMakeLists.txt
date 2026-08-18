cmake_minimum_required(VERSION 3.28)
project(Boids LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Boids "src/main.cpp" "src/Simulation.h" "src/Simulation.cpp" "src/Renderer.h" "src/Renderer.cpp" "src/Engine.h" "src/Engine.cpp")
target_compile_features(Boids PRIVATE cxx_std_17)
target_link_libraries(Boids PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Boids)
