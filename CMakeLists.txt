cmake_minimum_required(VERSION 3.13.4)

project(monty)

add_executable(monty src/main.c src/simulator.c)

target_include_directories(monty PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(monty
    PRIVATE
        pthread
)

#set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -g")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -fsanitize=address -Werror ")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fsanitize=leak ")