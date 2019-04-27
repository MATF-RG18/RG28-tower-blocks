cmake_minimum_required(VERSION 3.12)
# Ime vašeg projekta i jezik u kojem radite
project(RG28-tower-blocks C)

set(CMAKE_C_STANDARD 11)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(RG28-tower-blocks main.c)