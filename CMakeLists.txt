cmake_minimum_required(VERSION 3.29)
project(ASCII)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
