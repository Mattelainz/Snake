cmake_minimum_required(VERSION 3.25.0)
project(Snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SNAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROGRAM_SOURCES
#   ${SNAKE_SOURCE_DIR}/game/snake_body.hpp
    ${SNAKE_SOURCE_DIR}/view/graphicFuncs.cpp
    ${SNAKE_SOURCE_DIR}/view/graphicFuncs.hpp
    ${SNAKE_SOURCE_DIR}/view/mainMenu.cpp
    ${SNAKE_SOURCE_DIR}/view/mainMenu.hpp
)

add_executable(Snake ${SNAKE_SOURCE_DIR}/main.cpp ${PROGRAM_SOURCES})

target_include_directories(Snake PUBLIC ${SNAKE_SOURCE_DIR})

target_compile_options(Snake PRIVATE -Wall -Wextra -Wpedantic -Werror)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(${CURSES_FOUND})
  include_directories(${CURSES_INCLUDE_DIRS})
  target_link_libraries(Snake PUBLIC ${CURSES_LIBRARIES})
endif()