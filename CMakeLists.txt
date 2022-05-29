cmake_minimum_required(VERSION 3.16.3)

project(connect-four)

set(WARNINGS -Wall -Wextra -pedantic -Wshadow -Wno-pragma-once-outside-header -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -pedantic -Wswitch)

add_executable(${PROJECT_NAME} src/main.cpp src/board.cpp src/extras.cpp src/game.cpp src/menu.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)
target_compile_options(${PROJECT_NAME} PRIVATE ${WARNINGS})
# TODO: Fix warnings not showing for compiling object files

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
