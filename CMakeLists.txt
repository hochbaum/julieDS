cmake_minimum_required(VERSION 3.17)
project(julieds C)

set(CMAKE_C_STANDARD 11)

add_executable(julieds include/cpu/condition.h include/cpu/insn.h Core/cpu/insn.c include/cpu/armv5te/set.h Core/cpu/armv5te/set.c include/cpu/armv5te/cpu.h main.c Core/cpu/condition.c)