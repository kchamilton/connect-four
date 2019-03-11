cmake_minimum_required(VERSION 3.13)
project(connect_four C)

set(CMAKE_C_STANDARD 11)

add_executable(connect_four main.c gamestats.c gamestats.h mainmenu.c mainmenu.h endmenu.c endmenu.h)