cmake_minimum_required(VERSION 3.13)
project(pokemon_team)

set(CMAKE_CXX_STANDARD 17)

add_executable(pokemon_team main.cpp FindBestTeam.cpp Pokemon.cpp)