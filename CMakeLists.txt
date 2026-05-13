cmake_minimum_required(VERSION 3.10)
project(TeensRise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "game.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")
set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(OUT_DIR "$<TARGET_FILE_DIR:TeensRise>")

add_executable(TeensRise ${SOURCES} ${HEADERS})

target_include_directories(TeensRise PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_custom_command(TARGET TeensRise POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/translate"
            "${OUT_DIR}/translate"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/config"
            "${OUT_DIR}/config"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/maps"
            "${OUT_DIR}/maps"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/saves"
            "${OUT_DIR}/saves"
    COMMAND ${CMAKE_COMMAND} -E copy
            "${DATA_DIR}/tileset.txt"
            "${OUT_DIR}/tileset.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/lightning"
            "${OUT_DIR}/lightning"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}/items"
            "${OUT_DIR}/items"
)

if(MSVC)
    target_compile_options(TeensRise PRIVATE /W4)
else()
    target_compile_options(TeensRise PRIVATE -Wall -Wextra -Wpedantic)
endif()
