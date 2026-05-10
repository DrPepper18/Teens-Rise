cmake_minimum_required(VERSION 3.10)
project(TeensRise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "game.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

add_executable(TeensRise ${SOURCES} ${HEADERS})

target_include_directories(TeensRise PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(TeensRise PRIVATE /W4)
else()
    target_compile_options(TeensRise PRIVATE -Wall -Wextra -Wpedantic)
endif()
