cmake_minimum_required(VERSION 3.21)
project(laborator5__memory_leaks_Andra C)

set(CMAKE_C_STANDARD 11)

include_directories(laborator2-4/laborator2-4/laborator2-4)

add_executable(laborator5__memory_leaks_Andra
        laborator2-4/laborator2-4/laborator2-4/customSort.c
        laborator2-4/laborator2-4/laborator2-4/customSort.h
        laborator2-4/laborator2-4/laborator2-4/lista.c
        laborator2-4/laborator2-4/laborator2-4/lista.h
        laborator2-4/laborator2-4/laborator2-4/main.c
        laborator2-4/laborator2-4/laborator2-4/service.c
        laborator2-4/laborator2-4/laborator2-4/service.h
        laborator2-4/laborator2-4/laborator2-4/tranzactie.c
        laborator2-4/laborator2-4/laborator2-4/tranzactie.h
        laborator2-4/laborator2-4/laborator2-4/ui.c
        laborator2-4/laborator2-4/laborator2-4/ui.h
        laborator2-4/laborator2-4/laborator2-4/utils.c
        laborator2-4/laborator2-4/laborator2-4/utils.h)
