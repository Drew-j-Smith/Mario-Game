cmake_minimum_required(VERSION 2.8)
project(marioGame)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})

add_executable(marioGame Game.cpp)
target_link_libraries(marioGame sfml-graphics sfml-audio OpenAL)