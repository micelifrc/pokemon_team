cmake_minimum_required(VERSION 3.13)
project(pokemon_team)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES main.cpp FindBestTeam.cpp Pokedex.cpp Pokemon.cpp)

add_executable(pokemon_team ${SOURCE_FILES})