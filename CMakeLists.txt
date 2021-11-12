cmake_minimum_required(VERSION 3.20)
project(GOLF C)

set(CMAKE_C_STANDARD 11)

add_executable(GOLF golf.c main.c golf.h)