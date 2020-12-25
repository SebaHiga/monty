cmake_minimum_required(VERSION 3.13.4)

project(waz)

add_executable(waz src/main.c src/simulator.c)

target_include_directories(waz PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

#set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -g")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Werror -O3")