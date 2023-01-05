cmake_minimum_required(VERSION 3.18)

project(GameEngine)

add_library(GameEngine)

add_subdirectory(audio)
add_subdirectory(camera)
add_subdirectory(collision)
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(physics)
add_subdirectory(text)
add_subdirectory(ui)

add_subdirectory(external)

