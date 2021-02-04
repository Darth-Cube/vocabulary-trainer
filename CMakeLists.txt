cmake_minimum_required(VERSION 3.17)
project(Praktikum_5_Vokabeltrainer C)

set(CMAKE_C_STANDARD 11)

add_executable(Praktikum_5_Vokabeltrainer main.c library.h trainer.c modifying.c fileoperations.c)