cmake_minimum_required(VERSION 3.16.3)

project(connect-four)

add_executable(${PROJECT_NAME} src/main.cpp src/board.cpp src/extras.cpp src/game.cpp src/menu.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)